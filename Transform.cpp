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

	for (Transform* child : children) {
		child->Move(direction);
	}
}

void Transform::Rotate(Vector3 rotation) noexcept {
	this->rotation = {
		this->rotation.x + rotation.x,
		this->rotation.y + rotation.y,
		this->rotation.z + rotation.z
	};

	for (Transform* child : children) {
		child->Rotate(rotation);
	}
}

void Transform::Scale(Vector3 scale) noexcept {
	this->scale = {
		this->scale.x + scale.x,
		this->scale.y + scale.y,
		this->scale.z + scale.z
	};

	for (Transform* child : children) {
		child->Scale(scale);
	}

}

void Transform::Reset() noexcept {
	position = { 0.0f, 0.0f, 0.0f };
	rotation = { 0.0f, 0.0f,0.0f };
}

void Transform::SetPosition(Vector3 position) noexcept {
	Vector3 deltaPosition = {
		position.x - this->position.x,
		position.y - this->position.y,
		position.z - this->position.z
	};

	Move(deltaPosition);
}

void Transform::SetRotation(Vector3 rotation) noexcept {
	Vector3 deltaRotation = {
		rotation.x - this->rotation.x,
		rotation.y - this->rotation.y,
		rotation.z - this->rotation.z
	};

	Rotate(deltaRotation);
}

void Transform::SetScale(Vector3 scale) noexcept {
	Vector3 deltaScale = {
		scale.x - this->scale.x,
		scale.y - this->scale.y,
		scale.z - this->scale.z
	};

	Scale(deltaScale);
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
		return parent->GetModelMatrix() * Math::Translation(position) * Math::Rotation(rotation);
	}
	return Math::Translation(position) * Math::Rotation(rotation);
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
