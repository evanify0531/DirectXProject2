#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::Update()
{
}

void Transform::UpdateTransform()
{

	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation += Matrix::CreateRotationY(_localRotation.y);
	matRotation += Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;

	if (HasParent())
	{
		//스자이공부 -> scale 자전 이동? 공전 부모
		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = _matLocal;
	}
}
