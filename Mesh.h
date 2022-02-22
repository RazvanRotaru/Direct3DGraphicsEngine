#pragma once
#include "MinWindows.h"
#include "Math.h"
#include <vector>
#include <d3d11.h>

typedef USHORT Index;
typedef Vector2 UV;

struct Vertex {
	Vector3 position;
	Vector3 normal;
	UV tex_coord;
};

struct Material {
	alignas(16) Vector3 color = { 1.0f, 1.0f, 0 };
	float shininess;
	float kd;
	float ks;
	float padding;
};

constexpr Material defaultMaterial = {
	{1.0f, 0.0f, 1.0f},
	0.5f,
	0.1f,
	1.0f,
};


// TODO: this should be drawable, not the Actor
class Mesh {
	friend class Rigidbody;
public:
	enum class Type {
		Cube,
		Sphere,
		// ...
	};

	class Generator {
	public:
		static Mesh Create(Type type);
	private:
		static Mesh CreateCube();
	};
public:
	Mesh() = default;
	Mesh(Type, Material = defaultMaterial) noexcept;
	Mesh(std::vector<Vertex>, std::vector<Index>, Material = defaultMaterial) noexcept;

	std::vector<Vertex> GetVertices() noexcept;
	std::vector<Index> GetIndices() noexcept;
	Material GetMaterial() noexcept;
	static std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayout() noexcept;
	void LoadFromFile(LPCSTR path);

private:
	std::vector<Vertex> vertices;
	std::vector<Index> indices;
	Material material;
private:
	static std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
};

