#include "LightSource.h"
#include "BindableBase.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Math.h"
#include "Transform.h"

LightSource::LightSource(Actor* const& actor) 
	: Renderer(actor), cbuf(*(actor->GetWorld())) {
	cbData = {
			{ 0.0f,0.0f,0.0f },
			{ 0.05f,0.05f,0.05f },
			{ 1.0f,0.0f,0.0f /*1.0f*/},
			359.0f,
			1.0f,
			0.045f,
			0.0075f,
	};
	LoadConstantBuffers();
}

void LightSource::CastLight() const noexcept {
	cbData.pos = actor->GetTransform()->GetPosition();
	cbuf.Update(*(actor->GetWorld()), cbData);
	cbuf.Bind(*(actor->GetWorld()));
}

// TODO: add mesh will create another buffer
// either do not LoadConstantBuffers() in ctor or make Renderer::SetMesh() virtual and override
void LightSource::LoadConstantBuffers() {
	AddBind(std::make_unique<PixelConstantBuffer<PointLightCBuf>>(*(actor->GetWorld()), cbData));
}
