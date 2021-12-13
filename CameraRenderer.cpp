#include "CameraRenderer.h"
#include "Actor.h"
#include "Transform.h"

CameraRenderer::CameraRenderer(Actor* const& actor) 
	: Renderer(actor), cbuf(*(actor->GetWorld())) {
	cbData = {};
}

void CameraRenderer::SetViewport() const noexcept {
	cbData.pos = actor->GetTransform()->GetPosition();
	cbuf.Update(*(actor->GetWorld()), cbData);
	cbuf.Bind(*(actor->GetWorld()));
}

void CameraRenderer::LoadConstantBuffers() {
	AddBind(std::make_unique<PixelConstantBuffer<CameraCbuf>>(*(actor->GetWorld()), cbData, 2u));
}
