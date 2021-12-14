#pragma once
#include "Math.h"
#include "Actor.h"

class Camera : public Actor {
public:
	Camera(Graphics& gfx) noexcept;
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator= (const Camera&) = delete;

	DirectX::XMMATRIX GetViewMatrix() const noexcept;
	
	//void Bind() noexcept;
	void Move(Vector3 dir) noexcept;
	void Rotate(float dx, float dy) noexcept;

	void SetViewport() const noexcept;
	
private:
	void RotateOX(float dy);
	void RotateOY(float dx);

	void MoveForward(float dist);
	void MoveUpward(float dist);
	void MoveRight(float dist);

public:
	static constexpr float moveSpeed = 10.0f;
	static constexpr float rotationSpeed = 5e-1f;
};

