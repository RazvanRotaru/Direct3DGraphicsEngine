#pragma once
#include <vector>

class CollisionManager
{
public:
	CollisionManager();

	void CheckCollisions() const noexcept;
	void Add(class Rigidbody* rb) noexcept;
	void Remove(class Rigidbody* rb) noexcept;

	static CollisionManager* instance;
private:
	bool IsColliding(class Rigidbody* a, class Rigidbody* b) const noexcept;

	std::vector< class Rigidbody* > rigidbodies;
};

