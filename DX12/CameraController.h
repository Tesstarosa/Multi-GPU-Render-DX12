#pragma once
#include "Component.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GameTimer.h"


using namespace DirectX::SimpleMath;

class CameraController :
	public Component
{

	Keyboard* keyboard;
	Mouse* mouse;
	GameTimer* timer;


	double xMouseSpeed = 5;
	double yMouseSpeed = 5;
	
public:

	CameraController();

	void Update() override;;
	void Draw(ID3D12GraphicsCommandList* cmdList) override;;
};
