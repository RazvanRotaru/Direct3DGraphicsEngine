#pragma once
#include "MinWindows.h"
#include "Math.h"
#include <vector>
#include <d3d11.h>

typedef USHORT Index;
typedef Vector2 UV;

struct RGB {
	USHORT r;
	USHORT g;
	USHORT b;
};

struct Vertex {
	Vector3 position;
	RGB color;
	Vector3 normal;
	UV tex_coord;
};

struct Material {
	Vector3 ambient = { 1.0f, 1.0f, 1.0f };
	Vector3 diffuse = { 1.0f, 1.0f, 1.0f };
	Vector3 specular;
	float shininess;
};

class Mesh {
public:
	enum class Type {
		Box,
		Sphere
	};

	class Generator {
		// TODO (Add Factory)
	};
public:
	Mesh() noexcept = default;
	Mesh(Type) noexcept;
	Mesh(std::vector<Vertex>, std::vector<Index>, Material = {}) noexcept;

	std::vector<Vertex> GetVertices() noexcept;
	std::vector<Index> GetIndices() noexcept;
	Material GetMaterial() noexcept;

private:
	std::vector<Vertex> vertices;
	std::vector<Index> indices;
	Material material;
private:
	static std::vector<D3D11_INPUT_ELEMENT_DESC> layout;
};

