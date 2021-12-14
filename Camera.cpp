#include "Camera.h"
#include "Transform.h"
#include "CameraRenderer.h"

Camera::Camera(Graphics& gfx) noexcept : Actor(gfx) {
	renderer = new CameraRenderer(this);
}

void Camera::Move(Vector3 dir) noexcept {
	MoveRight(dir.x * moveSpeed);
	MoveUpward(dir.y * moveSpeed);
	MoveForward(dir.z * moveSpeed);
}

void Camera::Rotate(float dx, float dy) noexcept {
	RotateOX(dy * rotationSpeed);
	RotateOY(dx * rotationSpeed);
}

void Camera::SetViewport() const noexcept {
	dynamic_cast<CameraRenderer*>(renderer)->SetViewport();
}

void Camera::RotateOX(float dy) {
	const auto forward = Math::Transform(DirectX::XMLoadFloat3(&(transform->forward)),
		Math::RotateAround(transform->right, dy));
	DirectX::XMStoreFloat3(&(transform->forward), Math::Normalize(forward));

	DirectX::XMStoreFloat3(&(transform->up),
		Math::Normalize(
			Math::Cross(transform->right,
				transform->forward)));
}

void Camera::RotateOY(float dx) {
	DirectX::XMStoreFloat3(&(transform->forward), Math::Normalize(Math::Transform(
		DirectX::XMLoadFloat3(&(transform->forward)), Math::Rotation(dx, Axis::Y))));

	DirectX::XMStoreFloat3(&(transform->right), Math::Normalize(Math::Transform(
		DirectX::XMLoadFloat3(&(transform->right)), Math::Rotation(dx, Axis::Y))));

	DirectX::XMStoreFloat3(&(transform->up),
		Math::Normalize(
			Math::Cross(transform->right,
				transform->forward)));
}

void Camera::MoveForward(float dist) {
	transform->Move({
		transform->forward.x * dist,
		transform->forward.y * dist,
		transform->forward.z * dist
		});
}

void Camera::MoveUpward(float dist) {
	transform->Move({
		transform->up.x * dist,
		transform->up.y * dist,
		transform->up.z * dist
		});
}

void Camera::MoveRight(float dist) {
	Vector3 dir;
	DirectX::XMStoreFloat3(&dir, Math::Normalize(Vector3(transform->right.x, 0.0f, transform->right.z)));

	transform->Move({
		dir.x * dist,
		0.0f,
		dir.z * dist
		});
}

DirectX::XMMATRIX Camera::GetViewMatrix() const noexcept {
	return Math::LookTowards(transform->GetPosition(), transform->forward, transform->up);
}
