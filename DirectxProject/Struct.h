#pragma once

/*struct Vertex
{
	Vec3 position;
	//Color color;
	Vec2 uv;
};*/

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