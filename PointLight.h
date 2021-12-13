#pragma once
#include "ConstantBuffer.h"
#include "Actor.h"

class Graphics;
class Mesh;

class PointLight : public Actor {
public:
	PointLight(Graphics& gfx);
	void Reset() noexcept;
	void Draw() const noexcept(!IS_DEBUG);
	void Bind() const noexcept;

	virtual void Tick(float dt) override;
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
	PointLightCBuf cbData;
	mutable PixelConstantBuffer<PointLightCBuf> cbuf;
};