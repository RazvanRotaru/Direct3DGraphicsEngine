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
	Vector3 color = { 1.0f, 1.0f, 0 };
	float shininess;
};

class Mesh {
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
	Mesh() noexcept = default;
	Mesh(Type, Material = {}) noexcept;
	Mesh(std::vector<Vertex>, std::vector<Index>, Material = {}) noexcept;

	std::vector<Vertex> GetVertices() noexcept;
	std::vector<Index> GetIndices() noexcept;
	Material GetMaterial() noexcept;
	static std::vector<D3D11_INPUT_ELEMENT_DESC> GetLayout() noexcept;

private:
	std::vector<Vertex> vertices;
	std::vector<Index> indices;
	Material material;
private:
	static std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
};

