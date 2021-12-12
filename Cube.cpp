#include "Cube.h"
#include "Mesh.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"

Cube::Cube(Graphics& gfx) :
	pos({ 1.0f, 1.0f, 1.0f }) {
	if (!IsStaticInitialized()) {
		Material mat = {
			{ 1.0f, 1.0f, 0.0f }, // Color
			1
		};
		Mesh mesh = Mesh::Generator::Create(Mesh::Type::Cube);
		AddBind(std::make_unique<VertexBuffer>(gfx, mesh.GetVertices()));

		// might need to call AddIndexBuffer
		AddBind(std::make_unique<IndexBuffer>(gfx, mesh.GetIndices()));

		auto pVShader = std::make_unique<VertexShader>(gfx, TEXT("VertexShader.cso"));
		auto pVShaderBC = pVShader->GetBytecode();

		AddStaticBind(std::move(pVShader));
		AddStaticBind(std::make_unique<PixelShader>(gfx, TEXT("PixelShader.cso")));

		AddStaticBind(std::make_unique<PixelConstantBuffer<Material>>(gfx, mat));

		AddStaticBind(std::make_unique<InputLayout>(gfx, mesh.GetLayout(), pVShaderBC));
		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	} else {
		SetIndexFromStatic();
	}

	AddBind(std::make_unique<TransformCBuf>(gfx, *this));

	// TODO remove
	DirectX::XMStoreFloat3x3(
		&mt,
		DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f)
	);
}

void Cube::Update(float dt) noexcept {
	yaw = dt;
}

void Cube::SetPos(Vector3 pos) noexcept {
	this->pos = pos;
}

DirectX::XMMATRIX Cube::GetTransformXM() const noexcept {
	//return Math::Translation(pos.x, pos.y, pos.z);

	return DirectX::XMLoadFloat3x3(&mt) *
		Math::Rotation(yaw, Axis::Y) *
		Math::Rotation(pitch, Axis::X) *
		Math::Translation(0.0f, 0.0f, 5.0f);
}

void Cube::Update(float dx, float dy) noexcept {
	yaw = -dx * 3.0f;
	pitch = -dy * 3.0f;
}
