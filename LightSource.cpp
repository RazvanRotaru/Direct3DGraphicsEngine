#include "LightSource.h"
#include "BindableBase.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Math.h"
#include "Transform.h"

LightSource::LightSource(Actor* const& actor) 
	: Renderer(actor), cbuf(*(actor->GetWorld()), 1u) {
	cbData = {
			{ 0.0f,0.0f,0.0f },			// position (automatically updated)
			{ 0.15f,0.45f,0.35f },		// specular color
			{ 1.0f,0.0f,0.0f /*1.0f*/}, // light direction ????
			0.0f,						// cut-off angle
			0.0f,						// active cut-off
			0.045f,						// linear attenuation
			0.0075f,					// quadratic attenuation
	};
}

void LightSource::CastLight() const noexcept {
	cbData.pos = {
		actor->GetTransform()->GetPosition().x,
		actor->GetTransform()->GetPosition().y,
		-actor->GetTransform()->GetPosition().z,
	};
	cbuf.Update(*(actor->GetWorld()), cbData);
	cbuf.Bind(*(actor->GetWorld()));
}
