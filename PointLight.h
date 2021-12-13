#pragma once
#include "ConstantBuffer.h"
#include "Actor.h"

class Graphics;

class PointLight : public Actor {
public:
	PointLight(Graphics& gfx);
	void Reset() noexcept;
	void Bind() const noexcept;

	// TODO: Draw Lights after every object is drawn
	void Draw() const noexcept {}

	virtual void Tick(float dt) override {}
};