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
	//uint32 _width = 0;
	//uint32 _height = 0;

private:
	//Graphics
	Graphics* _graphics = nullptr;
	//shared_ptr<Graphics> _graphics;

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
	
	Vec3 _localScale = { 1.f, 1.f, 1.f };
	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	Vec3 _localRotation = { 0.f, 0.f, 0.f };

	//RasterizerState
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	//SamplerState
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;

	//BlendState
	ComPtr<ID3D11BlendState> _blendState = nullptr;
};