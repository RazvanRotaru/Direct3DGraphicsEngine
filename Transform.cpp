#include "Transform.h"
#include "Graphics.h"
#include "Actor.h"

Transform::Transform(Actor& actor) noexcept {
	this->actor = &actor;
	parent = nullptr;
	Reset();
}

Transform::Transform(Actor& actor, Vector3 position, Vector3 rotation) noexcept
	: Transform::Transform(actor) {
	Move(position);
	Rotate(rotation);
}

Transform::~Transform() {
	for (Transform* child : children) {
		child->SetParent(parent);
	}
}

void Transform::Move(Vector3 direction) noexcept {
	position = {
		position.x + direction.x,
		position.y + direction.y,
		position.z + direction.z
	};
}

void Transform::Rotate(Vector3 rotation) noexcept {
	this->rotation = {
		this->rotation.x + rotation.x,
		this->rotation.y + rotation.y,
		this->rotation.z + rotation.z
	};
}

void Transform::Scale(Vector3 scale) noexcept {
	this->scale = {
		this->scale.x + scale.x,
		this->scale.y + scale.y,
		this->scale.z + scale.z
	};
}

void Transform::Reset() noexcept {
	position = { 0.0f, 0.0f, 0.0f };
	rotation = { 0.0f, 0.0f,0.0f };
}

void Transform::SetPosition(Vector3 position) noexcept {
	this->position = {
		position.x,
		position.y,
		position.z
	};
}

void Transform::SetRotation(Vector3 rotation) noexcept {
	this->rotation = {
		rotation.x,
		rotation.y,
		rotation.z
	};
}

void Transform::SetScale(Vector3 scale) noexcept {
	this->scale = {
		scale.x,
		scale.y,
		scale.z
	};
}

Vector3 Transform::GetPosition() const noexcept {
	return position;
}

Vector3 Transform::GetRotation() const noexcept {
	return rotation;
}

Vector3 Transform::GetScale() const noexcept
{
	return scale;
}

DirectX::XMMATRIX Transform::GetModelMatrix() noexcept {
	// if parent exists add its rotation and translation
	if (parent != nullptr) {
		return Math::Scaling(scale) * Math::Rotation(rotation) * Math::Translation(position) * parent->GetModelMatrix();
	}

	// the multiplication order is inverse because thosee matrixes are transposed
	return Math::Scaling(scale) * Math::Rotation(rotation) * Math::Translation(position);
}

void Transform::SetParent(Transform* const& transform) noexcept {
	parent = transform;
}

Transform* Transform::GetParent() const noexcept {
	return parent;
}

void Transform::AddChild(Transform* const& transform) noexcept {
	children.push_back(transform);
}

std::vector<Transform*> Transform::GetChildren() const noexcept {
	return children;
}

Actor* Transform::GetActor() const noexcept {
	return actor;
}
