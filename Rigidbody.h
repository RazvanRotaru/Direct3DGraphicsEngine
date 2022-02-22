#pragma once
#include "Math.h"

class Rigidbody
{
	friend class CollisionManager;
public:
	Rigidbody(class Actor* actor);
	~Rigidbody();

	void OnCollision(Rigidbody* other);
private:
	class Transform* transform;
	Vector3 halfSize;
};

