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

void Transform::Reset() noexcept {
	position = { 0.0f, 0.0f, 0.0f };
	rotation = { 0.0f, 0.0f,0.0f };
}

void Transform::SetPosition(Vector3 position) noexcept {
	this->position = {
		this->position.x + position.x,
		this->position.y + position.y,
		this->position.z + position.z
	};

	for (Transform* child : children) {
		child->SetPosition(position);
	}
}

void Transform::SetRotation(Vector3 rotation) noexcept {
	this->rotation = {
				this->rotation.x + rotation.x,
				this->rotation.y + rotation.y,
				this->rotation.z + rotation.z
	};

	for (Transform* child : children) {
		child->SetRotation(rotation);
	}
}

Vector3 Transform::GetPosition() const noexcept {
	return position;
}

Vector3 Transform::GetRotation() const noexcept {
	return rotation;
}

DirectX::XMMATRIX Transform::GetModelMatrix() noexcept {
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
