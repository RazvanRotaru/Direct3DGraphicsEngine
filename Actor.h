#pragma once
#include <vector>
#include <string>

class Graphics;
class Transform;
class Mesh;
class Renderer;
class Rigidbody;

class Actor {
public:
	Actor(Graphics& gfx, Transform* const& parentTransform = nullptr) noexcept;
	~Actor();

	virtual void Start();
	virtual void Tick(float dt);

	void SetMesh(Mesh* const& mesh);

	Transform* GetTransform() const noexcept;
	Renderer*& GetRenderer() noexcept;
	Graphics*& GetWorld() noexcept;
	Mesh*& GetMesh() noexcept;

	// TODO: not ok to be public, but making private removes access from Rigidbody::OnCollision
	std::vector<std::string> luaScripts = { "LuaTest.lua" };


protected:
	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Renderer* renderer = nullptr;
	Rigidbody* rb = nullptr;


	static Graphics* world;
};
