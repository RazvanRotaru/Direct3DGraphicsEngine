#include "LightSource.h"
#include "BindableBase.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Math.h"
#include "Transform.h"

LightSource::LightSource(Actor* const& actor) 
	: Renderer(actor), cbuf(*(actor->GetWorld())) {
	cbData = {
			{ 0.0f,0.0f,0.0f },			// position (automatically updated)
			{ 0.15f,0.45f,0.35f },		// specular color
			{ 1.0f,0.0f,0.0f /*1.0f*/}, // light direction ????
			0.0f,						// cut-off angle
			0.0f,						// active cut-off
			0.045f,						// linear attenuation
			0.0075f,					// quadratic attenuation
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
