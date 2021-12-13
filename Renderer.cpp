#include "Renderer.h"
#include "Actor.h"
#include "Transform.h"
#include "BindableBase.h"
#include "Mesh.h"

Renderer::Renderer(Actor* const& actor)
{
    this->actor = actor;
}

void Renderer::SetMesh(Mesh* const& mesh)
{
	this->mesh = mesh;
	LoadBuffers();
	LoadConstantBuffers();
}

void Renderer::LoadBuffers()
{
	AddBind(std::make_unique<VertexBuffer>(*(actor->world), mesh->GetVertices()));
	AddBind(std::make_unique<IndexBuffer>(*(actor->world), mesh->GetIndices()));

	AddBind(std::make_unique<Texture>(*(actor->world), Surface::FromFile(texture)));

	if (!IsStaticInitialized()) {
		
		AddStaticBind(std::make_unique<PixelShader>(*(actor->world), pixelShader));
		auto pVShader = std::make_unique<VertexShader>(*(actor->world), vertexShader);
		auto pVShaderBC = pVShader->GetBytecode();
		AddStaticBind(std::move(pVShader));

		AddStaticBind(std::make_unique<Sampler>(*(actor->world)));

		AddStaticBind(std::make_unique<InputLayout>(*(actor->world), mesh->GetLayout(), pVShaderBC));
		AddStaticBind(std::make_unique<Topology>(*(actor->world), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	AddBind(std::make_unique<TransformCBuf>(*(actor->world), *this));
}

void Renderer::LoadConstantBuffers() {
	AddBind(std::make_unique<PixelConstantBuffer<Material>>(*(actor->world), mesh->GetMaterial()));
}

DirectX::XMMATRIX Renderer::GetTransformXM() const noexcept
{
    return actor->GetTransform()->GetModelMatrix();
}
