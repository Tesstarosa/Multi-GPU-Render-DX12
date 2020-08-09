#pragma once
#include <d3d12.h>
#include <wrl.h>

#include <string>
#include <memory>

struct DescriptorHandle
{
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle;
};

class GResource
{
	static uint64_t  resourceId;

	
public:
	
	GResource(const std::wstring& name = L"");
	GResource(const D3D12_RESOURCE_DESC& resourceDesc,
				const std::wstring& name = L"",
	         const D3D12_CLEAR_VALUE* clearValue = nullptr);
	GResource(Microsoft::WRL::ComPtr<ID3D12Resource>& resource, const std::wstring& name = L"");
	GResource(const GResource& copy);
	GResource(GResource&& move);

	GResource& operator=(const GResource& other);
	GResource& operator=(GResource&& other) noexcept;

	virtual ~GResource();

	bool IsValid() const;

	
	Microsoft::WRL::ComPtr<ID3D12Resource> GetD3D12Resource() const;

	D3D12_RESOURCE_DESC GetD3D12ResourceDesc() const;

	virtual void SetD3D12Resource(Microsoft::WRL::ComPtr<ID3D12Resource> d3d12Resource,
	                              const D3D12_CLEAR_VALUE* clearValue = nullptr);

	
	virtual DescriptorHandle GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc = nullptr) const = 0;

	
	virtual DescriptorHandle GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc = nullptr) const = 0;


	
	void SetName(const std::wstring& name);

	
	
	virtual void Reset();

protected:

	uint64_t id = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> dxResource;
	std::unique_ptr<D3D12_CLEAR_VALUE> clearValue;
	std::wstring resourceName;
};
