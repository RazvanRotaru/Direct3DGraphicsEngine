#include "Mesh.h"

std::vector<D3D11_INPUT_ELEMENT_DESC> Mesh::layout =
{
	D3D11_INPUT_ELEMENT_DESC {
		"POSITION",						// SemanticName
		0u,								// SemanticIndex
		DXGI_FORMAT_R32G32B32_FLOAT,	// Format
		0u,								// InputSlot
		D3D11_APPEND_ALIGNED_ELEMENT,	// AlignedByteOffset
		D3D11_INPUT_PER_VERTEX_DATA,	// InputSlotClass
		0u,								// InstanceDataStepRate
	},
	D3D11_INPUT_ELEMENT_DESC {
		"NORMAL",						// SemanticName
		0u,								// SemanticIndex
		DXGI_FORMAT_R32G32B32_FLOAT,	// Format
		0u,								// InputSlot
		D3D11_APPEND_ALIGNED_ELEMENT,	// AlignedByteOffset
		D3D11_INPUT_PER_VERTEX_DATA,	// InputSlotClass
		0u,								// InstanceDataStepRate
	},
	D3D11_INPUT_ELEMENT_DESC {
		"UV",							// SemanticName
		0u,								// SemanticIndex
		DXGI_FORMAT_R32G32_FLOAT,		// Format
		0u,								// InputSlot
		D3D11_APPEND_ALIGNED_ELEMENT,	// AlignedByteOffset
		D3D11_INPUT_PER_VERTEX_DATA,	// InputSlotClass
		0u,								// InstanceDataStepRate
	}
};


Mesh::Mesh(std::vector<Vertex> vertices,
		   std::vector<Index> indices,
		   Material material) noexcept
	: vertices(vertices), indices(indices), material(material) {
}

std::vector<Vertex> Mesh::GetVertices() noexcept {
	return vertices;
}

std::vector<Index> Mesh::GetIndices() noexcept {
	return indices;
}

Material Mesh::GetMaterial() noexcept {
	return material;
}

std::vector<D3D11_INPUT_ELEMENT_DESC> Mesh::GetLayout() noexcept {
	return layout;
}

Mesh Mesh::Generator::Create(Type type) {
	switch (type) {
	case Mesh::Type::Cube:
		return CreateCube();
	}
	return Mesh();
}

Mesh Mesh::Generator::CreateCube() {
	constexpr float side = 0.5f;

	std::vector<Vertex> vertices(24);

	// front face
	vertices[0] = {
		{ -side,-side,-side,},
		{ 0.0f, 0.0f, 1.0f, },
		{ 0.0f, 0.0f, }
	};
	vertices[1] = {
		{ side,-side,-side },
		{ 0.0f, 0.0f, 1.0f, },
		{ 1.0f, 0.0f, }
	};
	vertices[2] = {
		{ -side,side,-side },
		{ 0.0f, 0.0f, 1.0f, },
		{ 0.0f, 1.0f, }
	};
	vertices[3] = {
		{ side,side,-side },
		{ 0.0f, 0.0f, 1.0f, },
		{ 1.0f, 1.0f, }
	};

	// back face
	vertices[4] = {
		{ -side,-side,side },
		{ 0.0f, 0.0f, -1.0f, },
		{ 0.0f, 0.0f, }
	};
	vertices[5] = {
		{ side,-side,side },
		{ 0.0f, 0.0f, -1.0f, },
		{ 1.0f, 0.0f, }
	};
	vertices[6] = {
		{ -side,side,side },
		{ 0.0f, 0.0f, -1.0f, },
		{ 0.0f, 1.0f, }

	};
	vertices[7] = {
		{ side,side,side },
		{ 0.0f, 0.0f, -1.0f, },
		{ 1.0f, 1.0f, }

	};

	// left face
	vertices[8] = {
		{ -side,-side,-side },
		{ -1.0f, 0.0f, 0.0f, },
		{ 0.0f, 0.0f, }
	};
	vertices[9] = {
		{ -side,side,-side },
		{ -1.0f, 0.0f, 0.0f, },
		{ 1.0f, 0.0f, }
	};
	vertices[10] = {
		{ -side,-side,side },
		{ -1.0f, 0.0f, 0.0f, },
		{ 0.0f, 1.0f, }
	};
	vertices[11] = {
		{ -side,side,side },
		{ -1.0f, 0.0f, 0.0f, },
		{ 1.0f, 1.0f, }
	};

	// right face
	vertices[12] = {
		{ side, -side, -side },
		{ 1.0f, 0.0f, 0.0f, },
		{ 0.0f, 0.0f, }
	};
	vertices[13] = {
		{ side,side,-side },
		{ 1.0f, 0.0f, 0.0f, },
		{ 1.0f, 0.0f, }
	};
	vertices[14] = {
		{ side,-side,side },
		{ 1.0f, 0.0f, 0.0f, },
		{ 0.0f, 1.0f, }
	};
	vertices[15] = {
		{ side,side,side },
		{ 1.0f, 0.0f, 0.0f, },
		{ 1.0f, 1.0f, }
	};

	// bottom face
	vertices[16] = {
		{ -side,-side,-side },
		{ 0.0f, -1.0f, 0.0f, },
		{ 0.0f, 0.0f, }
	};
	vertices[17] = {
		{ side,-side,-side },
		{ 0.0f, -1.0f, 0.0f, },
		{ 1.0f, 0.0f, }
	};
	vertices[18] = {
		{ -side,-side,side },
		{ 0.0f, -1.0f, 0.0f, },
		{ 0.0f, 1.0f, }
	};
	vertices[19] = {
		{ side,-side,side },
		{ 0.0f, -1.0f, 0.0f, },
		{ 1.0f, 1.0f, }
	};

	// top face
	vertices[20] = {
		{ -side,side,-side },
		{ 0.0f, 1.0f, 0.0f, },
		{ 0.0f, 0.0f, }
	};
	vertices[21] = {
		{ side,side,-side },
		{ 0.0f, 1.0f, 0.0f, },
		{ 1.0f, 0.0f, }
	};
	vertices[22] = {
		{ -side,side,side },
		{ 0.0f, 1.0f, 0.0f, },
		{ 0.0f, 1.0f, }
	};
	vertices[23] = {
		{ side,side,side },
		{ 0.0f, 1.0f, 0.0f, },
		{ 1.0f, 1.0f, }

	};


	std::vector<Index> indices = {
		0,2, 1,    2,3,1,
		4,5, 7,    4,7,6,
		8,10, 9,  10,11,9,
		12,13,15, 12,15,14,
		16,17,18, 18,17,19,
		20,23,21, 20,22,23
	};

	return Mesh(vertices, indices);
}
