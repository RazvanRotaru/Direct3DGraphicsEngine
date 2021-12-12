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
		"COLOR",						// SemanticName
		0u,								// SemanticIndex
		DXGI_FORMAT_R8G8B8A8_UNORM,		// Format
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
