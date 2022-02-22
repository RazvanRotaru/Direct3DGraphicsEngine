#include "CollisionManager.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Math.h"

CollisionManager* CollisionManager::instance = nullptr;

CollisionManager::CollisionManager()
{
	if (instance == nullptr) {
		instance = this;
		rigidbodies.clear();
	} else {
		delete this;
	}
}

void CollisionManager::CheckCollisions() const noexcept
{
	auto sz = rigidbodies.size();
	for (size_t i = 0; i < sz; ++i) {
		for (size_t j = i + 1; j < sz; ++j) {
			auto& a = rigidbodies[i];
			auto& b = rigidbodies[j];
			if (IsColliding(a, b)) {
				a->OnCollision(b);
				b->OnCollision(a);
			}
		}
	}
}

bool CollisionManager::IsColliding(Rigidbody* a, Rigidbody* b) const noexcept
{
	auto maxA = Math::Add(a->transform->GetPosition(), a->halfSize);
	auto minA = Math::Substract(a->transform->GetPosition(), a->halfSize);

	auto maxB = Math::Add(b->transform->GetPosition(), b->halfSize);
	auto minB = Math::Substract(b->transform->GetPosition(), b->halfSize);

	return (minA.x <= maxB.x && maxA.x >= minB.x)
		&& (minA.y <= maxB.y && maxA.y >= minB.y)
		&& (minA.z <= maxB.z && maxA.z >= minB.z);
}


void CollisionManager::Add(Rigidbody* rb) noexcept {
	rigidbodies.push_back(rb);
}

void CollisionManager::Remove(Rigidbody* rb) noexcept
{
	for (size_t i = 0; i < rigidbodies.size(); i++) {
		if (rigidbodies[i] == rb) {
			rigidbodies.erase(rigidbodies.begin() + i);
		}
	}
}
