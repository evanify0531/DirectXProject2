#include "pch.h"
#include "CameraMove.h"
#include "GameObject.h"

void CameraMove::Update()
{
	auto pos = GetTransform()->GetPosition();
	pos.y += 0.005f;
	GetTransform()->SetPosition(pos);
}
