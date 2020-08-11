#include "Material.h"


#include "d3dApp.h"
#include "GMemory.h"
#include "PSO.h"

UINT Material::materialIndexGlobal = 0;

MaterialConstants& Material::GetMaterialConstantData()
{
	return matConstants;
}

PSO* Material::GetPSO() const
{
	return pso;
}

void Material::SetDiffuseTexture(Texture* texture)
{
	textures.push_back(texture);
	DiffuseMapIndex = texture->GetTextureIndex();
}

Material::Material(std::string name, PSO* pso): Name(std::move(name)), pso(pso)
{
	materialIndex = materialIndexGlobal++;
}


void Material::InitMaterial(GMemory& textureHeap)
{
	gpuTextureHandle = textureHeap.GetGPUHandle(this->DiffuseMapIndex ); 
	cpuTextureHandle = textureHeap.GetCPUHandle(this->DiffuseMapIndex );

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;


	auto& device = DXLib::D3DApp::GetDevice();
	
	//TODO: �������� ��� ����� �� ����� ����������, � �������� ������ ������ � ���������
	if (textures[0])
	{
		auto desc = textures[0]->GetResource()->GetDesc();

		if (textures[0])
		{
			srvDesc.Format = GetSRGBFormat(desc.Format);
		}
		else
		{
			srvDesc.Format = (desc.Format);
		}


		switch (pso->GetType())
		{
		case PsoType::SkyBox:
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
			srvDesc.TextureCube.MipLevels = desc.MipLevels;
			srvDesc.TextureCube.MostDetailedMip = 0;
			break;
		case PsoType::AlphaSprites:
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2DARRAY;
			srvDesc.Texture2DArray.MostDetailedMip = 0;
			srvDesc.Texture2DArray.MipLevels = -1;
			srvDesc.Texture2DArray.FirstArraySlice = 0;
			srvDesc.Texture2DArray.ArraySize = desc.DepthOrArraySize;
			break;
		default:
			{
				srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MostDetailedMip = 0;
				srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
				srvDesc.Texture2D.MipLevels = desc.MipLevels;
			}
		}
		device.CreateShaderResourceView(textures[0]->GetResource(), &srvDesc, cpuTextureHandle);
	}

	if (normalMap)
	{
		srvDesc.Format = normalMap->GetResource()->GetDesc().Format;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
		srvDesc.Texture2D.MipLevels = normalMap->GetResource()->GetDesc().MipLevels;
		auto cpuNormalMapTextureHandle = textureHeap.GetCPUHandle(NormalMapIndex);
		device.CreateShaderResourceView(normalMap->GetResource(), &srvDesc, cpuNormalMapTextureHandle);
	}
}

void Material::Draw(ID3D12GraphicsCommandList* cmdList) const
{
	//TODO: �������� � �����, ����� �� ���-�� ��� ������, ��� ���������� � ���������� ��������, ����� �������� ������ �������� ������� �������, � ������ � ����������� �� ������� � ������� �������� � ��������� ��� � ��������� ������� ��� ���� (Texture2DArray, TextureCube)
	const auto psoType = pso->GetType();
	if (psoType == PsoType::SkyBox)
	{
		cmdList->SetGraphicsRootDescriptorTable(StandardShaderSlot::SkyMap, gpuTextureHandle);
	}
}

void Material::Update()
{
	if (NumFramesDirty > 0)
	{
		matConstants.DiffuseAlbedo = DiffuseAlbedo;
		matConstants.FresnelR0 = FresnelR0;
		matConstants.Roughness = Roughness;
		XMStoreFloat4x4(&matConstants.MaterialTransform, XMMatrixTranspose(XMLoadFloat4x4(&MatTransform)));
		matConstants.DiffuseMapIndex = DiffuseMapIndex;
		matConstants.NormalMapIndex = NormalMapIndex;

		NumFramesDirty--;
	}
}

std::string& Material::GetName()
{
	return Name;
}
