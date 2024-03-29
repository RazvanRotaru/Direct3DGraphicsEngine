#pragma once
#include "Math.h"

class Camera {
public:
	Camera() noexcept;
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator= (const Camera&);

	void Reset() noexcept;
	DirectX::XMMATRIX GetMatrix() const noexcept;
	
	void Move(Vector3 to) noexcept;
	void Rotate(float dx, float dy) noexcept;
private:
	Vector3 position;
	float yaw;
	float pitch;

	static constexpr float moveSpeed = 10.0f;
	static constexpr float rotationSpeed = 4e-3f;
};

