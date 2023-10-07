#pragma once
class Game
{
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = NULL;
	//uint32 _width = 0;
	//uint32 _height = 0;

private:
	//Graphics
	shared_ptr<Graphics> _graphics;

	//Geometry
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	//Vertex Shader
	shared_ptr<VertexShader> _vertexShader;
	
	//Pixel Shader
	shared_ptr<PixelShader> _pixelShader;

	//SRV (Shader Resource View)
	shared_ptr<Texture> _texture1;

	//Constant Buffer
	TransformData _transformData;
	shared_ptr <ConstantBuffer<TransformData>> _constantBuffer;
	
	Vec3 _localScale = { 1.f, 1.f, 1.f };
	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	Vec3 _localRotation = { 0.f, 0.f, 0.f };

	//RasterizerState
	shared_ptr<RasterizerState> _rasterizerState;

	//SamplerState
	shared_ptr<SamplerState> _samplerState;

	//BlendState
	shared_ptr<BlendState> _blendState;
};