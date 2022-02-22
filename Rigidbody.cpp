#include "Rigidbody.h"
#include "Actor.h"
#include "Mesh.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "LuaManager.h"

Rigidbody::Rigidbody(Actor* actor)
{
	Vector3 maxSz = { 0, 0, 0 };
	for (auto& vert : actor->GetMesh()->vertices) {
		maxSz.x = std::max(maxSz.x, vert.position.x);
		maxSz.y = std::max(maxSz.y, vert.position.y);
		maxSz.z = std::max(maxSz.z, vert.position.z);
	}

	halfSize = {
		maxSz.x / 2,
		maxSz.y / 2,
		maxSz.z / 2
	};

	transform = actor->GetTransform();

	CollisionManager::instance->Add(this);
}

Rigidbody::~Rigidbody()
{
	CollisionManager::instance->Remove(this);
}

void Rigidbody::OnCollision(Rigidbody* other)
{
	for (auto& script : transform->GetActor()->luaScripts) {
		LuaManager::instance->CallMethod(script, "OnCollision");
	}
}
