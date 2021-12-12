#include "VertexBuffer.h"
#include "Mesh.h"

VertexBuffer::VertexBuffer(Graphics& gfx, const std::vector<Vertex>& vertices)
	: stride(sizeof(Vertex)) {
	INIT_INFOMNGR(gfx);

	D3D11_BUFFER_DESC desc = {
		UINT(sizeof(Vertex) * vertices.size()),		// ByteWidth
		D3D11_USAGE_DEFAULT,						// Usage
		D3D11_BIND_VERTEX_BUFFER,					// BindFlags
		0u,											// CPUAccessFlags
		0u,											// MiscFlags
		sizeof(Vertex),								// StructuredByteStride
	};

	D3D11_SUBRESOURCE_DATA data = {
		vertices.data(),							// pSysMem
		0u,											// SysMemPitch
		0u,											// SysMemSlicePitch
	};

	GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&desc, &data, &pVertexBuffer));
}

void VertexBuffer::Bind(Graphics& gfx) noexcept {
	const UINT offset = 0u;
	GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
