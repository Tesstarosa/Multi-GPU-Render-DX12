#include "GResource.h"

#include <utility>

#include "d3dApp.h"
#include "d3dUtil.h"

uint64_t GResource::resourceId = 0;

GResource::GResource(const std::wstring& name)
	: resourceName(std::move(name))
{
	id = ++resourceId;
}

GResource::GResource(const D3D12_RESOURCE_DESC& resourceDesc, const D3D12_CLEAR_VALUE* clearValue,
                   const std::wstring& name)
{
	id = ++resourceId;
	
	auto& device = DXLib::D3DApp::GetApp().GetDevice();
	
	if (clearValue)
	{
		this->clearValue = std::make_unique<D3D12_CLEAR_VALUE>(*clearValue);
	}

	ThrowIfFailed(device.CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_COMMON,
		this->clearValue.get(),
		IID_PPV_ARGS(&dxResource)
	));

	SetName(name);
}

GResource::GResource(Microsoft::WRL::ComPtr<ID3D12Resource>& resource, const std::wstring& name)
	: dxResource(std::move(resource))
{
	id = ++resourceId;
	
	SetName(name);
}

GResource::GResource(const GResource& copy)
	: id(copy.id)
	  , dxResource(copy.dxResource)
	  , clearValue(std::make_unique<D3D12_CLEAR_VALUE>(*copy.clearValue))
	  , resourceName(copy.resourceName)
{
	
}

GResource::GResource(GResource&& move)
	: id(std::move(move.id))
	  , dxResource(std::move(move.dxResource))
	  , clearValue(std::move(move.clearValue))
, resourceName(std::move(move.resourceName))
{
}

GResource& GResource::operator=(const GResource& other)
{
	if (this != &other)
	{
		id = other.id;
		dxResource = other.dxResource;
		resourceName = other.resourceName;
		if (other.clearValue)
		{
			clearValue = std::make_unique<D3D12_CLEAR_VALUE>(*other.clearValue);
		}
	}

	return *this;
}

GResource& GResource::operator=(GResource&& other) noexcept
{
	if (this != &other)
	{
		id = other.id;
		dxResource = other.dxResource;
		resourceName = other.resourceName;
		clearValue = std::move(other.clearValue);

		other.dxResource.Reset();
		other.resourceName.clear();
	}

	return *this;
}


GResource::~GResource()
{
	GResource::Reset();
}

bool GResource::IsValid() const
{
	return (dxResource != nullptr);
}

Microsoft::WRL::ComPtr<ID3D12Resource> GResource::GetD3D12Resource() const
{
	return dxResource;
}

D3D12_RESOURCE_DESC GResource::GetD3D12ResourceDesc() const
{
	D3D12_RESOURCE_DESC resDesc = {};
	if (dxResource)
	{
		resDesc = dxResource->GetDesc();
	}

	return resDesc;
}

void GResource::SetD3D12Resource(ComPtr<ID3D12Resource> d3d12Resource,
                                 const D3D12_CLEAR_VALUE* clearValue)
{
	dxResource = std::move(d3d12Resource);
	if (this->clearValue)
	{
		this->clearValue.reset();
		this->clearValue = std::make_unique<D3D12_CLEAR_VALUE>(*clearValue);
	}
	else
	{
		this->clearValue = std::make_unique<D3D12_CLEAR_VALUE>(*clearValue);
	}
	
	SetName(resourceName);
}

void GResource::SetName(const std::wstring& name)
{
	resourceName = name;
	if (dxResource && !resourceName.empty())
	{
		dxResource->SetName(resourceName.c_str());
	}
}

bool GResource::CheckFormatSupport(D3D12_FORMAT_SUPPORT1 formatSupport) const
{
	return (m_FormatSupport.Support1 & formatSupport) != 0;
}

bool GResource::CheckFormatSupport(D3D12_FORMAT_SUPPORT2 formatSupport) const
{
	return (m_FormatSupport.Support2 & formatSupport) != 0;
}

void GResource::Reset()
{
	if(dxResource)
	dxResource.Reset();

	if(clearValue)
	clearValue.reset();
}
