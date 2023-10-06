#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	//_width = GWinSizeX;
	//_height = GWinSizeY;

	//Graphics
	//_graphics = new Graphics(hwnd);
	_graphics = make_shared <Graphics>(hwnd);
	_vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice());
	_indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
	_inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexShader = make_shared<VertexShader>(_graphics->GetDevice());
	_pixelShader = make_shared<PixelShader>(_graphics->GetDevice());
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_texture1 = make_shared<Texture>(_graphics->GetDevice());

	//TODO

	//CreateGeometry
	//Vertex Data
	GeometryHelper::CreateRectangle(_geometry);
	//vertex Buffer	
	_vertexBuffer->Create(_geometry->GetVertices());
	//Index Buffer
	_indexBuffer->Create(_geometry->GetIndices());

	//create vertex shader
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	
	//CreateInputLayout
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	//create pixel shader
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();
	
	//Create shader resource view (SRV)
	_texture1->Create(L"tmnt2.png");

	//create constant buffer
	_constantBuffer->Create();
}

void Game::Update()
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

void Game::Render()
{
	_graphics->RenderBegin();

	//TODO
	{
		//IA
		uint32 stride = sizeof(VertexTextureData); //will fix later
		uint32 offset = 0;

		auto _deviceContext = _graphics->GetDeviceContext();

		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout->GetComPtr().Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//VS
		_deviceContext->VSSetShader(_vertexShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer->GetComPtr().GetAddressOf());

		//RS
		_deviceContext->RSSetState(_rasterizerState.Get());

		//PS
		_deviceContext->PSSetShader(_pixelShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _texture1->GetComPtr().GetAddressOf());
		//_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		//OM
		_deviceContext->OMSetBlendState(_blendState.Get(), nullptr, 0xFFFFFFFF);
		
		//_deviceContext->Draw(_vertices.size(), 0);
		_deviceContext->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
	}

	_graphics->RenderEnd();
}

void Game::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;
	HRESULT hr = _graphics->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
}


void Game::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.MipLODBias = 0.0f;
	desc.MaxAnisotropy = 16;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.BorderColor[0] = 0.f;
	desc.BorderColor[1] = 1.f;
	desc.BorderColor[2] = 0.f;
	desc.BorderColor[3] = 1.f;
	desc.MinLOD = FLT_MIN;
	desc.MaxLOD = FLT_MAX;

	HRESULT hr = _graphics->GetDevice()->CreateSamplerState(&desc, _samplerState.GetAddressOf());
}

void Game::CreateBlendState()
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = _graphics->GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);
}