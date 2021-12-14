#include "CameraRenderer.h"
#include "Actor.h"
#include "Transform.h"

CameraRenderer::CameraRenderer(Actor* const& actor) 
	: Renderer(actor), cbuf(*(actor->GetWorld())) {
	cbData = {Vector3(4.0f, 4.0f, 3.0f)};
	LoadConstantBuffers();
}

void CameraRenderer::SetViewport() const noexcept {
	//cbData.pos = actor->GetTransform()->GetPosition();
	cbData.pos = Vector3(10.0f, 10.0f, 10.f);
	cbuf.Update(*(actor->GetWorld()), cbData);
	cbuf.Bind(*(actor->GetWorld()));
}

void CameraRenderer::LoadConstantBuffers() {
	AddBind(std::make_unique<PixelConstantBuffer<CameraCbuf>>(*(actor->GetWorld()), cbData, 2u));
}
