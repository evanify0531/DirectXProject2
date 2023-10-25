#pragma once

class GameObject
{
public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

public:
	void Update();
	void Render(shared_ptr<Pipeline> pipeline);

private:
	ComPtr<ID3D11Device> _device;

	//Geometry
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	//shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	//Vertex Shader
	shared_ptr<VertexShader> _vertexShader;

	//Pixel Shader
	shared_ptr<PixelShader> _pixelShader;

	//SRV (Shader Resource View)
	shared_ptr<Texture> _texture1;

	//RasterizerState
	shared_ptr<RasterizerState> _rasterizerState;

	//SamplerState
	shared_ptr<SamplerState> _samplerState;

	//BlendState
	shared_ptr<BlendState> _blendState;

private:
	//Constant Buffer
	TransformData _transformData;
	shared_ptr <ConstantBuffer<TransformData>> _constantBuffer;
	
	shared_ptr<Transform> _transform = make_shared<Transform>();

	shared_ptr<Transform> _parent = make_shared<Transform>();
};

