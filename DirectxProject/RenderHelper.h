#pragma once

struct TransformData
{
	/*Vec3 offset;
	float dummy;*/
	Matrix matWorld = Matrix::Identity;
};

struct CameraData
{
	/*Vec3 offset;
	float dummy;*/
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

//gpu넘겨줄때 16바이트 정렬
struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;
	float useAnimation;

	float padding;

};

