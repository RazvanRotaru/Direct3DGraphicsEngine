#include "IndexBuffer.h"
#include "GraphicsThrowMacros.h"

IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<USHORT>& indices)
	: count((UINT)indices.size()) {
	INIT_INFOMNGR(gfx);

	D3D11_BUFFER_DESC  desc = {
		UINT(count * sizeof(USHORT)),	// ByteWidth
		D3D11_USAGE_DEFAULT,			// Usage
		D3D11_BIND_INDEX_BUFFER,		// BindFlags
		0u,								// CPUAccessFlags
		0u,								// MiscFlags
		sizeof(USHORT),					// StructuredByteStride
	};
	
	D3D11_SUBRESOURCE_DATA data = {
		indices.data(),					// pSysMem
		0u,								// SysMemPitch
		0u,								// SysMemSlicePitch
	};

	GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&desc, &data, &pIndexBuffer));
}

void IndexBuffer::Bind(Graphics& gfx) noexcept {
	GetContext(gfx)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const noexcept {
	return count;
}
