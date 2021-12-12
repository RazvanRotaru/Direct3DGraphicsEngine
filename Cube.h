#pragma once
#include "DrawableBase.h"

class Cube : public DrawableBase<Cube> {
public:
	Cube(Graphics& gfx);
	void Update(float dt) noexcept override;
	void SetPos(DirectX::XMFLOAT3 pos) noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	DirectX::XMFLOAT3 pos;
	// TODO remove
private:
	float yaw = 0.0f;
	float pitch = 0.0f;
	DirectX::XMFLOAT3X3 mt;
public:
	void Update(float dx, float dy) noexcept override;
};

