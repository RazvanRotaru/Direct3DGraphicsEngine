#include "Camera.h"
#include "Transform.h"

Camera::Camera(Graphics& gfx) noexcept : Actor(gfx) {
}

void Camera::Move(Vector3 dir) noexcept {
	// compute global movement direction
	float pitch = transform->GetRotation().y;
	float yaw = transform->GetRotation().z;
	DirectX::XMStoreFloat3(&dir, Math::Transform(
		DirectX::XMLoadFloat3(&dir),
		Math::Rotation(0.0f, pitch, yaw) *
		Math::Scaling(moveSpeed, moveSpeed, moveSpeed)
	));

	transform->Move(dir);
}

void Camera::Rotate(float dx, float dy) noexcept {
	float pitch = transform->GetRotation().y;
	float yaw = transform->GetRotation().z;
	yaw = Math::WrapAngle(yaw + dx * rotationSpeed);
	pitch = Math::Clamp(pitch + dy * rotationSpeed, -Math::PI * 0.5f, Math::PI * 0.5f);

	transform->SetRotation(Vector3(0.0f, pitch, yaw));
}

DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept {
	return Math::Translation(
		-transform->GetPosition().x,
		-transform->GetPosition().y,
		-transform->GetPosition().z)
		* Math::Rotation(0.0f, -transform->GetRotation().y, -transform->GetRotation().z);
}
