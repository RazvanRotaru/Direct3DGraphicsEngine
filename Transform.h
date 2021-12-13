#pragma once
#include "Math.h"
#include <vector>

class Actor;

class Transform {
public:
	Transform(Actor& actor) noexcept;
	Transform(Actor& actor, Vector3 position, Vector3 rotation) noexcept;
	~Transform();


	void Move(Vector3 direction) noexcept;
	void Rotate(Vector3 rotation) noexcept;
	void Scale(Vector3 scale) noexcept;
	void Reset() noexcept;

	void SetPosition(Vector3 position) noexcept;
	void SetRotation(Vector3 rotation) noexcept;
	void SetScale(Vector3 scale) noexcept;

	Vector3 GetPosition() const noexcept;
	Vector3 GetRotation() const noexcept;
	Vector3 GetScale() const noexcept;
	DirectX::XMMATRIX GetModelMatrix() noexcept;

	void SetParent(Transform* const& transform) noexcept;
	Transform* GetParent() const noexcept;

	void AddChild(Transform* const& transform) noexcept;
	std::vector<Transform*> GetChildren() const noexcept;

	Actor* GetActor() const noexcept;
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);

	Actor* actor;

	Transform* parent;
	std::vector<Transform*> children;
};

