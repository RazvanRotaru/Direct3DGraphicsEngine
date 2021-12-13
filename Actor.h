#pragma once
class Graphics;
class Transform;
class Mesh;


// Remove Drawabel, make mesh drawable
class Actor {
	friend class Renderer;
public:
	Actor(Graphics& gfx, Transform* const& parentTransform = nullptr) noexcept;
	~Actor();

	virtual void Start();
	virtual void Tick(float dt);

	void SetMesh(Mesh* const& mesh);

	Transform* GetTransform() const noexcept;
protected:
	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Renderer* renderer = nullptr;

	static Graphics* world;
};

