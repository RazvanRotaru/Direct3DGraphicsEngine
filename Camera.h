#pragma once
#include "Math.h"
#include "Actor.h"

// inherit from Actor
class Camera {
public:
	Camera() noexcept;
	~Camera() = default;
	Camera(const Camera&) = delete;
	Camera& operator= (const Camera&);

	void Reset() noexcept;
	DirectX::XMMATRIX GetMatrix() const noexcept;
	
	//void Bind() noexcept;

	void Move(Vector3 to) noexcept;
	void Rotate(float dx, float dy) noexcept;
private:
	Vector3 position;
	float yaw;
	float pitch;

	static constexpr float moveSpeed = 10.0f;
	static constexpr float rotationSpeed = 5e-1f;
//private:
//	struct CameraCbuf {
//		Vector3 pos;
//		float padding;
//	};
//	
//	mutable CameraCbuf cbData;
//	mutable PixelConstantBuffer<CameraCbuf> cbuf;
};

