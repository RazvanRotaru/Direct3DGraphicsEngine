#pragma once
#include <DirectXMath.h>
#include <math.h>
#include <algorithm>

typedef DirectX::XMFLOAT3X3 ModelMatrix;
typedef DirectX::XMFLOAT3X3 ViewMatrix;
typedef DirectX::XMFLOAT3X3 ProjMatrix;

typedef DirectX::XMFLOAT4 Vector4;
typedef DirectX::XMFLOAT3 Vector3;
typedef DirectX::XMFLOAT2 Vector2;


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

	static DirectX::XMVECTOR Normalize(DirectX::XMVECTOR v);
	static DirectX::XMVECTOR Normalize(Vector3 v);

	static DirectX::XMVECTOR Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b);
	static DirectX::XMVECTOR Cross(DirectX::XMFLOAT3 a, DirectX::XMFLOAT4 b);
	static DirectX::XMVECTOR Cross(DirectX::XMFLOAT4 a, DirectX::XMFLOAT4 b);

	static DirectX::XMMATRIX Transpose(DirectX::XMMATRIX mat);

	static DirectX::XMMATRIX Rotation(float angle, Axis axis);
	static DirectX::XMMATRIX Rotation(float roll, float pitch, float yaw);
	static DirectX::XMMATRIX Rotation(Vector3 eulerAngles);

	static DirectX::XMMATRIX RotateAround(Vector3 axis, float angle);

	static DirectX::XMMATRIX Translation(float x, float y, float z);
	static DirectX::XMMATRIX Translation(Vector3 position);

	static DirectX::XMMATRIX Scaling(float x, float y, float z);
	static DirectX::XMMATRIX Scaling(Vector3 scale);

	static DirectX::XMMATRIX Projection(float fov, float aspectRatio, float zNear, float zFar);

	static DirectX::XMVECTOR Transform(DirectX::XMVECTOR vec, DirectX::XMMATRIX mat);

	static DirectX::XMMATRIX LookAt(Vector3 position, Vector3 target, Vector3 up);
	static DirectX::XMMATRIX LookTowards(Vector3 position, Vector3 direction, Vector3 up);

	static float ClipCoursor(float pos, float wndSize);

	template<typename T>
	static T WrapAngle(T theta) {
		constexpr T twoPi = (T)2 * (T)PI_D;
		const T mod = fmod(theta, twoPi);
		if (mod > (T)PI_D) {
			return mod - twoPi;
		} else if (mod < (T)PI_D) {
			return mod + twoPi;
		}
		return mod;
	}

	template<typename T>
	static T Clamp(T val, T min, T max) {
		float fVal = (float)val;
		float fMin = (float)min;
		float fMax = (float)max;
		return std::clamp(fVal, fMin, fMax);
	}

	template<typename T>
	static constexpr T Lerp(const T& src, const T& dst, float alpha) {
		return src + (dst - src) * alpha;
	}

	template<typename T>
	static constexpr T Deg2Rad(T deg) {
		return deg * PI / (T)180.0;
	}
public:
	static constexpr float PI = 3.14159265f;
	static constexpr double PI_D = 3.1415926535897932;
};