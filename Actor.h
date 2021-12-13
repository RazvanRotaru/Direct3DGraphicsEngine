#pragma once
class Graphics;
class Transform;
class Mesh;
class Renderer;

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
protected:
	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Renderer* renderer = nullptr;

	static Graphics* world;
};

