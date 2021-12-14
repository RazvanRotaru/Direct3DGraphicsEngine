#pragma once
#include "ConstantBuffer.h"
#include "Renderer.h"

class LightSource : public Renderer {
public:
	LightSource(Actor* const& actor);

	void CastLight() const noexcept;
private:
	struct PointLightCBuf {
		alignas(16) Vector3 pos;
		alignas(16) Vector3 specularColor;
		alignas(16) Vector3 lightDir;
		float cutOffAngle;
		float isActive;
		float attLin;
		float attQuad;
	};
private:
	mutable PointLightCBuf cbData;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;
};

