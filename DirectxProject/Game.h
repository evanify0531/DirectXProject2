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
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

	void CreateGeometry();

	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

	void CreateVS();

	void CreateRasterizerState();

	void CreatePS();

	void CreateSamplerState();

	void CreateBlendState();

	void CreateSRV();

	void CreateInputLayout();

private:
	HWND _hwnd = NULL;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	//Device and SwapChain
	ComPtr<ID3D11Device>  _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	ComPtr<IDXGISwapChain> _swapChain = nullptr;

	// Render Target View
	ComPtr<ID3D11RenderTargetView> _renderTargetView = nullptr;

	// Misc
	D3D11_VIEWPORT _viewport = { 0 };
	float _clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.f };

	//Geometry
	vector<Vertex> _vertices;
	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;

	//Vertex Shader
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;
	
	//Pixel Shader
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	//SRV (Shader Resource View)
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;

	//Constant Buffer
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

	//RasterizerState
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	//SamplerState
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;

	//BlendState
	ComPtr<ID3D11BlendState> _blendState = nullptr;
};