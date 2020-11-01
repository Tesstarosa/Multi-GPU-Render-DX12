#pragma once
#include "d3d12.h"
#include "SimpleMath.h"
#include "MemoryAllocator.h"
#include <memory>

#include "GCommandList.h"

class GameObject;

class Component
{
public:

	GameObject* gameObject = nullptr;

	Component();

	virtual void Update() = 0;
	virtual void Draw(std::shared_ptr<PEPEngine::Graphics::GCommandList> cmdList) = 0;
};