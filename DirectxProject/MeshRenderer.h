#pragma once
#include "Component.h"

class MeshRenderer :
    public Component
{
    using Super = Component;
public:
    MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
    virtual ~MeshRenderer();
	virtual void Update() override;

private:
	void Render(shared_ptr<Pipeline> pipeline);

private:
	ComPtr<ID3D11Device> _device;

	//Mesh
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	//Material
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
	CameraData _cameraData;
	shared_ptr <ConstantBuffer<CameraData>> _cameraBuffer;

	TransformData _transformData;
	shared_ptr <ConstantBuffer<TransformData>> _transformBuffer;

	//shared_ptr<Transform> _transform = make_shared<Transform>();

	//shared_ptr<Transform> _parent = make_shared<Transform>();
};

