#pragma once
#include <DirectXMath.h>

enum class Axis {
	X,
	Y,
	Z
};

class Math {
public:
	static float Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT2 b);
	static float Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	static float Dot(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b);
	static float Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT3 b);
	static float Dot(DirectX::XMFLOAT2 a, DirectX::XMFLOAT4 b); 
	static float Dot(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b);
	
	static DirectX::XMVECTOR Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	static DirectX::XMVECTOR Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b);
	static DirectX::XMVECTOR Cross(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b);
	
	static DirectX::XMMATRIX Transpose(DirectX::XMMATRIX mat);

	static DirectX::XMMATRIX Rotation(float angle, Axis axis);
	static DirectX::XMMATRIX Translation(float x, float y, float z);
	static DirectX::XMMATRIX Scaling(float x, float y, float z);
	static DirectX::XMMATRIX Projection(float fov, float aspectRatio, float zNear, float zFar);

	static float ClipCoursor(float pos, float wndSize);
};
