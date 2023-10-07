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
	_rasterizerState = make_shared<RasterizerState>(_graphics->GetDevice());
	_samplerState = make_shared<SamplerState>(_graphics->GetDevice());
	_blendState = make_shared<BlendState>(_graphics->GetDevice());

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

	_rasterizerState->Create();
	_samplerState->Create();
	_blendState->Create();
	
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
		_deviceContext->RSSetState(_rasterizerState->GetComPtr().Get());

		//PS
		_deviceContext->PSSetShader(_pixelShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _texture1->GetComPtr().GetAddressOf());
		//_deviceContext->PSSetShaderResources(1, 1, _shaderResourceView2.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState->GetComPtr().GetAddressOf());

		//OM
		_deviceContext->OMSetBlendState(_blendState->GetComPtr().Get(), _blendState->GetBlendFactor(), _blendState->GetSampleMask());
		
		//_deviceContext->Draw(_vertices.size(), 0);
		_deviceContext->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
	}

	_graphics->RenderEnd();
}