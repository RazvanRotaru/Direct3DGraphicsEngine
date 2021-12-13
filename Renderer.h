#pragma once
#include "DrawableBase.h"
#include "MinWindows.h"

class Mesh;
class Actor;
class Bindable;

// TODO: Might make an base class Component and std::vector<Component> in Actor
class Renderer : public DrawableBase<Mesh>
{
public:
	Renderer(Actor* const& actor);

	void SetMesh(Mesh* const& mesh);
protected:
	virtual void LoadBuffers();
	virtual void LoadConstantBuffers();
public:
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept override;

	// TODO: remove
	virtual void Update(float dt) noexcept override {}
	virtual void Update(float dx, float dy) noexcept override {}

protected:
	Actor* actor;
	Mesh* mesh;

	LPCWSTR vertexShader = TEXT("VertexShader.cso");
	LPCWSTR pixelShader = TEXT("PixelShader.cso");

	LPCSTR texture = "Resources\\Textures\\10.png";
};
