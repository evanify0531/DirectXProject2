#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device)
{
	//Create Geometry
	//Vertex Data
	//_geometry = make_shared<Geometry<VertexTextureData>>();
	_geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateRectangle(_geometry, Color(0.0f, 1.f, 0.f, 1.0f));

	//Vertex Buffer
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	//Index Buffer
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	//Vertex Shader
	_vertexShader = make_shared<VertexShader>(_device);
	//_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	_vertexShader->Create(L"Color.hlsl", "VS", "vs_5_0");

	//Input Layout
	_inputLayout = make_shared<InputLayout>(_device);
	//_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());
	_inputLayout->Create(VertexColorData::descs, _vertexShader->GetBlob());

	//Pixel Shader
	_pixelShader = make_shared<PixelShader>(_device);
	//_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");
	_pixelShader->Create(L"Color.hlsl", "PS", "ps_5_0");

	//Rasterizer State
	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	//Blend State
	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();

	//Constant Buffer
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_device, deviceContext);
	_constantBuffer->Create();

	//Create shader resource view (SRV)
	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"tmnt2.png");
	

	//Sampler State
	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	//Scale Rotation Translation SRT
	_localPosition.x += 0.001f;
	//_transformData.offset.x += -0.0003f;
	//_transformData.offset.y += 0.0003f;
	//SRT
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation += Matrix::CreateRotationY(_localRotation.y);
	matRotation += Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = ((matScale * matRotation) * matTranslation);

	_transformData.matWorld = matWorld;

	//write data into constant buffer
	_constantBuffer->CopyData(_transformData);
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);
	pipeline->SetConstantBuffer(0, SS_VertexShader, _constantBuffer);
	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
