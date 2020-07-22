#pragma once

#include "d3dUtil.h"
#include "DXAllocator.h"
#include <array>

using namespace Microsoft::WRL;

class RootSignature
{
	ComPtr<ID3D12RootSignature> signature;

	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers();;

	custom_vector<CD3DX12_ROOT_PARAMETER> slotRootParameters = DXAllocator::CreateVector<CD3DX12_ROOT_PARAMETER>();

	void AddParameter(CD3DX12_ROOT_PARAMETER parameter);

	custom_vector<D3D12_STATIC_SAMPLER_DESC> staticSampler = DXAllocator::CreateVector<D3D12_STATIC_SAMPLER_DESC>();

public:

	void AddDescriptorParameter(CD3DX12_DESCRIPTOR_RANGE* rangeParameters, UINT size,
	                            D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);

	void AddConstantBufferParameter(UINT shaderRegister, UINT registerSpace = 0,
	                                D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);

	void AddConstantParameter(UINT value, UINT shaderRegister, UINT registerSpace = 0,
	                          D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);

	void AddShaderResourceView(UINT shaderRegister, UINT registerSpace = 0,
	                           D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);

	void AddUnorderedAccessView(UINT shaderRegister, UINT registerSpace = 0,
	                            D3D12_SHADER_VISIBILITY visibility = D3D12_SHADER_VISIBILITY_ALL);

	void AddStaticSampler(CD3DX12_STATIC_SAMPLER_DESC sampler);
	void AddStaticSampler(D3D12_STATIC_SAMPLER_DESC sampler);;

	void Initialize(ID3D12Device* device);

	ComPtr<ID3D12RootSignature> GetRootSignature() const;
};
