#include "Renderer.h"
#include "Actor.h"
#include "Transform.h"
#include "BindableBase.h"
#include "Mesh.h"

Renderer::Renderer(Actor* const& actor)
{
    this->actor = actor;
	this->mesh = nullptr;
}

void Renderer::SetMesh(Mesh* const& mesh)
{
	this->mesh = mesh;
	LoadBuffers();
	LoadConstantBuffers();
}

void Renderer::LoadBuffers()
{
	AddBind(std::make_unique<VertexBuffer>(*(actor->GetWorld()), mesh->GetVertices()));
	AddBind(std::make_unique<IndexBuffer>(*(actor->GetWorld()), mesh->GetIndices()));

	AddBind(std::make_unique<Texture>(*(actor->GetWorld()), Surface::FromFile(texture)));

	if (!IsStaticInitialized()) {
		
		AddStaticBind(std::make_unique<PixelShader>(*(actor->GetWorld()), pixelShader));
		auto pVShader = std::make_unique<VertexShader>(*(actor->GetWorld()), vertexShader);
		auto pVShaderBC = pVShader->GetBytecode();
		AddStaticBind(std::move(pVShader));

		AddStaticBind(std::make_unique<Sampler>(*(actor->GetWorld())));

		AddStaticBind(std::make_unique<InputLayout>(*(actor->GetWorld()), mesh->GetLayout(), pVShaderBC));
		AddStaticBind(std::make_unique<Topology>(*(actor->GetWorld()), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	AddBind(std::make_unique<TransformCBuf>(*(actor->GetWorld()), *this));
}

void Renderer::LoadConstantBuffers() {

	Material mat = {
			{ 1.0f, 1.0f, 0.0f }, // Color
			1
	};

	AddBind(std::make_unique<PixelConstantBuffer<Material>>(*(actor->GetWorld()), mat, 1u));
}

DirectX::XMMATRIX Renderer::GetTransformXM() const noexcept
{
    return actor->GetTransform()->GetModelMatrix();
}
