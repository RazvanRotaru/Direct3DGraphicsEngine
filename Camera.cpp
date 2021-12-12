#include "Camera.h"

Camera::Camera() noexcept {
	Reset();
}

Camera& Camera::operator=(const Camera& other) {
	this->position = other.position;

	this->yaw = other.yaw;
	this->pitch = other.pitch;

	return *this;
}

void Camera::Reset() noexcept {
	position = { 0.0f, 0.0f, -20.0f };
	yaw = 0.0f;
	pitch = 0.0f;
}

void Camera::Move(Vector3 to) noexcept {
	// compute global movement direction
	DirectX::XMStoreFloat3(&to, Math::Transform(
		DirectX::XMLoadFloat3(&to),
		Math::Rotation(0.0f, pitch, yaw) *
		Math::Scaling(moveSpeed, moveSpeed, moveSpeed)
	));

	position = {
		position.x + to.x,
		position.y + to.y,
		position.z + to.z
	};
}

void Camera::Rotate(float dx, float dy) noexcept {
	yaw = Math::WrapAngle(yaw + dx * rotationSpeed);
	pitch = Math::Clamp(pitch + dy * rotationSpeed, -Math::PI * 0.5f, Math::PI * 0.5f);
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept {
	return Math::Translation(-position.x, -position.y, -position.z)
		* Math::Rotation(0.0f, -pitch, -yaw);
}
