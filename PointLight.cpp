#include "PointLight.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Math.h"
#include "Transform.h"
#include "BindableBase.h"

PointLight::PointLight(Graphics& gfx)
	: Actor(gfx), cbuf(gfx) {
	Reset();
}

void PointLight::Reset() noexcept {
	cbData = {
		{ 0.0f,7.0f,14.0f },
		{ 0.05f,0.05f,0.05f },
		{ 1.0f,1.0f,1.0f },
		359.0f,
		1.0f,
		0.045f,
		0.0075f,
	};
}

void PointLight::Draw() const noexcept(!IS_DEBUG) {
	//transform->SetPos(cbData.pos);
	//mesh.Draw(gfx);
	transform->SetPosition(cbData.pos);
}

void PointLight::Bind() const noexcept {
	cbuf.Update(*world, cbData);
	cbuf.Bind(*world);
}

void PointLight::Tick(float dt) {
}

//void PointLight::LoadBuffers()
//{
//	Material mat = {
//		{ 1.0f, 1.0f, 0.0f }, // Color
//		1
//	};
//	Mesh mesh = Mesh::Generator::Create(Mesh::Type::Cube);
//
//	AddBind(std::make_unique<VertexBuffer>(*world, mesh.GetVertices()));
//	AddBind(std::make_unique<IndexBuffer>(*world, mesh.GetIndices()));
//	AddBind(std::make_unique<PixelConstantBuffer<PointLightCBuf>>(*world, cbData, 1u));
//
//	// TODO: remove
//	AddBind(std::make_unique<Texture>(*world, Surface::FromFile("Resources\\Textures\\10.png")));
//
//	if (!IsStaticInitialized()) {
//
//		AddStaticBind(std::make_unique<PixelShader>(*world, TEXT("PixelShader.cso")));
//		auto pVShader = std::make_unique<VertexShader>(*world, TEXT("VertexShader.cso"));
//		auto pVShaderBC = pVShader->GetBytecode();
//		AddStaticBind(std::move(pVShader));
//
//		AddStaticBind(std::make_unique<Sampler>(*world));
//
//		AddStaticBind(std::make_unique<InputLayout>(*world, mesh.GetLayout(), pVShaderBC));
//		AddStaticBind(std::make_unique<Topology>(*world, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
//	}
//
//	AddBind(std::make_unique<TransformCBuf>(*world, *this));
//}
