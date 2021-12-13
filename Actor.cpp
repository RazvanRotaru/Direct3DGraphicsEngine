#include "Actor.h"
#include "Mesh.h"
#include "Transform.h"
#include "BindableBase.h"
#include "Renderer.h"

Graphics* Actor::world;

Actor::Actor(Graphics& gfx, Transform* const& parentTransform) noexcept {
	if (world == nullptr) {
		world = &gfx;
	}

	transform = new Transform(*this);
	if (parentTransform != nullptr) {
		transform->SetParent(parentTransform);
		(parentTransform)->AddChild(transform);
	}

	renderer = new Renderer(this);
}

Actor::~Actor() {
	delete transform;
	mesh = nullptr;
}

void Actor::Start() {
}

void Actor::Tick(float dt) {
	if (renderer != nullptr) {
		renderer->Draw(*world);
	}
}

void Actor::SetMesh(Mesh* const& mesh) {
	this->mesh = mesh;
	renderer->SetMesh(mesh);
}

Transform* Actor::GetTransform() const noexcept {
	return transform;
}

Renderer*& Actor::GetRenderer() noexcept
{
	return renderer;
}

Graphics*& Actor::GetWorld() noexcept {
	return world;
}
