#pragma once

#include "ShaderBuffersData.h"
#include "GTexture.h"

using namespace  PEPEngine;
using namespace Graphics;

class GCrossAdapterResource;

struct SplitFrameResource
{
public:

	SplitFrameResource(std::shared_ptr<GDevice>* devices, UINT deviceCount,  UINT passCount, UINT materialCount);
	SplitFrameResource(const SplitFrameResource& rhs) = delete;
	SplitFrameResource& operator=(const SplitFrameResource& rhs) = delete;
	~SplitFrameResource();

	
	
	std::shared_ptr<GCrossAdapterResource> CrossAdapterBackBuffer = nullptr;
	
	GTexture PrimeDeviceBackBuffer;

	custom_vector<GDescriptor> RenderTargetViewMemory = MemoryAllocator::CreateVector<GDescriptor>();
	
	custom_vector<std::shared_ptr<ConstantBuffer<PassConstants>>> PassConstantBuffers = MemoryAllocator::CreateVector < std::shared_ptr<ConstantBuffer<PassConstants>>>();

	custom_vector<std::shared_ptr<ConstantBuffer<SsaoConstants>>> SsaoConstantBuffers = MemoryAllocator::CreateVector < std::shared_ptr<ConstantBuffer<SsaoConstants>>>();

	custom_vector<std::shared_ptr<UploadBuffer<MaterialConstants>>> MaterialBuffers = MemoryAllocator::CreateVector < std::shared_ptr<UploadBuffer<MaterialConstants>>>();
	
	

	UINT64 FenceValue = 0;
};