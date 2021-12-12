#include "Math.h"

float Math::Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat2(&a, aVec);
	DirectX::XMStoreFloat2(&b, bVec);
	return DirectX::XMVectorGetX(DirectX::XMVector2Dot(aVec, bVec));
}

float Math::Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat3(&a, aVec);
	DirectX::XMStoreFloat3(&b, bVec);
	return DirectX::XMVectorGetX(DirectX::XMVector3Dot(aVec, bVec));
}

float Math::Dot(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat4(&a, aVec);
	DirectX::XMStoreFloat4(&b, bVec);
	return DirectX::XMVectorGetX(DirectX::XMVector4Dot(aVec, bVec));
}

float Math::Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT3 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat2(&a, aVec);
	DirectX::XMStoreFloat3(&b, bVec);
	return DirectX::XMVectorGetX(DirectX::XMVector2Dot(aVec, bVec));
}

float Math::Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT4 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat2(&a, aVec);
	DirectX::XMStoreFloat4(&b, bVec);
	return DirectX::XMVectorGetX(DirectX::XMVector2Dot(aVec, bVec));
}

float Math::Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat3(&a, aVec);
	DirectX::XMStoreFloat4(&b, bVec);
	return DirectX::XMVectorGetX(DirectX::XMVector3Dot(aVec, bVec));
}

DirectX::XMMATRIX Math::Transpose(DirectX::XMMATRIX mat) {
	return DirectX::XMMatrixTranspose(mat);
}

DirectX::XMVECTOR Math::Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat3(&a, aVec);
	DirectX::XMStoreFloat3(&b, bVec);

	return DirectX::XMVector3Cross(aVec, bVec);
}

DirectX::XMVECTOR Math::Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat3(&a, aVec);
	DirectX::XMStoreFloat4(&b, bVec);

	return DirectX::XMVector3Cross(aVec, bVec);
}

DirectX::XMVECTOR Math::Cross(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b) {
	DirectX::XMVECTOR aVec{}, bVec{};
	DirectX::XMStoreFloat4(&a, aVec);
	DirectX::XMStoreFloat4(&b, bVec);

	return DirectX::XMVector3Cross(aVec, bVec);
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
	DirectX::XMVECTOR rotVec{};
	DirectX::XMStoreFloat3(&eulerAngles, rotVec);
	return DirectX::XMMatrixRotationRollPitchYawFromVector(rotVec);
}

DirectX::XMMATRIX Math::Translation(float x, float y, float z) {
	return DirectX::XMMatrixTranslation(x, y, z);
}

DirectX::XMMATRIX Math::Translation(Vector3 position) {
	DirectX::XMVECTOR tVec{};
	DirectX::XMStoreFloat3(&position, tVec);
	return DirectX::XMMatrixTranslationFromVector(tVec);
}

DirectX::XMMATRIX Math::Scaling(float x, float y, float z) {
	return DirectX::XMMatrixScaling(x, y, z);
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

