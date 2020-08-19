#include "ObjectMover.h"
#include "d3dApp.h"
#include "GameObject.h"
#include "SampleApp.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

void ObjectMover::Draw(std::shared_ptr<GCommandList> cmdList)
{
}

void ObjectMover::Update()
{
	const float dt = DXLib::D3DApp::GetApp().GetTimer()->DeltaTime();

	Vector3 offset = Vector3::Zero;
	if (keyboard->KeyIsPressed(VK_UP))
	{
		offset.z += 1.0f * dt;
	}
	if (keyboard->KeyIsPressed(VK_DOWN))
	{
		offset.z -= 1.0f * dt;
	}
	if (keyboard->KeyIsPressed(VK_LEFT))
	{
		offset.x -= 1.0f * dt;
	}
	if (keyboard->KeyIsPressed(VK_RIGHT))
	{
		offset.x += 1.0f * dt;
	}

	if (keyboard->KeyIsPressed(VK_NEXT))
	{
		offset.y -= 1.0f * dt;
	}
	if (keyboard->KeyIsPressed(VK_PRIOR))
	{
		offset.y += 1.0f * dt;
	}

	
	if (offset != Vector3::Zero)
		gameObject->GetTransform()->AdjustPosition(offset);

	auto position = gameObject->GetTransform()->GetPosition();
	
	OutputDebugStringW((std::to_wstring(position.x) + L" " + std::to_wstring(position.y) + L" "+ std::to_wstring(position.z) + L" " + L"\n").c_str());
}

ObjectMover::ObjectMover()
{
	keyboard = ((DXLib::SampleApp&)DXLib::SampleApp::GetApp()).GetKeyboard();
}
