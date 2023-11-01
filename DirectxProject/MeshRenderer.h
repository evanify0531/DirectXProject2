#pragma once
#include "Component.h"
#include "Material.h"
#include "Shader.h"

class Mesh;
class Shader;
class Material;


class MeshRenderer :
    public Component
{
    using Super = Component;
public:
    MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
    virtual ~MeshRenderer();


	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh;  }
	void SetShader(shared_ptr<Shader> shader) { _material->SetShader(shader); }
	void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); }
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	
	shared_ptr<Mesh> GetMesh() { return _mesh; }
	shared_ptr<InputLayout> GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
	shared_ptr<VertexShader> GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
	shared_ptr<PixelShader> GetPixelShader() { return GetMaterial()->GetShader()->GetPixelShader(); }
	shared_ptr<Texture> GetTexture() { return GetMaterial()->GetTexture();  }
	shared_ptr<Material> GetMaterial() { return _material; }


private:
	ComPtr<ID3D11Device> _device;

	friend class RenderManager;

	//Mesh
	shared_ptr<Mesh> _mesh;

	//Material
	shared_ptr<Material> _material;


private:

};

