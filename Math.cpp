#include "Math.h"

float Math::Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b) {
	return DirectX::XMVectorGetX(DirectX::XMVector2Dot(DirectX::XMLoadFloat2(&a), DirectX::XMLoadFloat2(&b)));
}

float Math::Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	return DirectX::XMVectorGetX(DirectX::XMVector3Dot(DirectX::XMLoadFloat3(&a), DirectX::XMLoadFloat3(&b)));
}

float Math::Dot(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b) {
	return DirectX::XMVectorGetX(DirectX::XMVector4Dot(DirectX::XMLoadFloat4(&a), DirectX::XMLoadFloat4(&b)));
}

float Math::Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT3 b) {
	return DirectX::XMVectorGetX(DirectX::XMVector2Dot(DirectX::XMLoadFloat2(&a), DirectX::XMLoadFloat3(&b)));
}

float Math::Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT4 b) {
	return DirectX::XMVectorGetX(DirectX::XMVector2Dot(DirectX::XMLoadFloat2(&a), DirectX::XMLoadFloat4(&b)));
}

float Math::Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b) {
	return DirectX::XMVectorGetX(DirectX::XMVector3Dot(DirectX::XMLoadFloat3(&a), DirectX::XMLoadFloat4(&b)));
}

DirectX::XMMATRIX Math::Transpose(DirectX::XMMATRIX mat) {
	return DirectX::XMMatrixTranspose(mat);
}

DirectX::XMVECTOR Math::Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	return DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&a), DirectX::XMLoadFloat3(&b));
}

DirectX::XMVECTOR Math::Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b) {
	return DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&a), DirectX::XMLoadFloat4(&b));
}

DirectX::XMVECTOR Math::Cross(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b) {
	return DirectX::XMVector3Cross(DirectX::XMLoadFloat4(&a), DirectX::XMLoadFloat4(&b));
}

DirectX::XMMATRIX Math::Rotation(float angle, Axis axis) {
	switch (axis) {
	case Axis::X:
		return DirectX::XMMatrixRotationX(angle);
	case Axis::Y:
		return DirectX::XMMatrixRotationY(angle);
	case Axis::Z:
		return DirectX::XMMatrixRotationZ(angle);
	}
	throw "Unknown axis";
}

DirectX::XMMATRIX Math::Rotation(float roll, float pitch, float yaw) {
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
}

DirectX::XMMATRIX Math::Rotation(Vector3 eulerAngles) {
	return DirectX::XMMatrixRotationRollPitchYawFromVector(DirectX::XMLoadFloat3(&eulerAngles));
}

DirectX::XMMATRIX Math::Translation(float x, float y, float z) {
	return DirectX::XMMatrixTranslation(x, y, z);
}

DirectX::XMMATRIX Math::Translation(Vector3 position) {
	return DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position));
}

DirectX::XMMATRIX Math::Scaling(float x, float y, float z) {
	return DirectX::XMMatrixScaling(x, y, z);
}

DirectX::XMMATRIX Math::Scaling(Vector3 scale)
{
	return DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale));
}

DirectX::XMMATRIX Math::Projection(float fov, float aspectRatio, float zNear, float zFar) {
	return DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, zNear, zFar);
}

DirectX::XMVECTOR Math::Transform(DirectX::XMVECTOR vec, DirectX::XMMATRIX mat) {
	return DirectX::XMVector3Transform(vec, mat);
}

float Math::ClipCoursor(float pos, float wndSize) {
	return pos / (wndSize * 0.5f) - 1.0f;
}

