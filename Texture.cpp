#include "Texture.h"
#include "Surface.h"
#include "GraphicsThrowMacros.h"

namespace wrl = Microsoft::WRL;

Texture::Texture(Graphics& gfx, const Surface& s) {
	INIT_INFOMNGR(gfx);

	// create texture resource
	D3D11_TEXTURE2D_DESC textureDesc = {
		s.GetWidth(),				// Width
		s.GetHeight(),				// Height
		1u,							// MipLevels
		1u,							// ArraySize
		DXGI_FORMAT_B8G8R8A8_UNORM,	// Format
		DXGI_SAMPLE_DESC {
			1u,		// Count
			0u		// Quality
		},
		D3D11_USAGE_DEFAULT,		// Usage
		D3D11_BIND_SHADER_RESOURCE, // BindFlags
		0u,							// CPUAccessFlags
		0u,							// MiscFlags
	};
	D3D11_SUBRESOURCE_DATA data = {
		s.GetBufferPtr(),						// pSysMem
		s.GetWidth() * sizeof(Surface::Color),	// SysMemPitch
	};

	wrl::ComPtr<ID3D11Texture2D> pTexture;
	GFX_THROW_INFO(GetDevice(gfx)->CreateTexture2D(
		&textureDesc, &data, &pTexture
	));

	// create the resource view on the texture
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {
		textureDesc.Format,				// Format
		D3D11_SRV_DIMENSION_TEXTURE2D,	//ViewDimension
		{
			0u,	// MostDetailedMip
			1u	// MipLevels
		}
	};

	GFX_THROW_INFO(GetDevice(gfx)->CreateShaderResourceView(
		pTexture.Get(), &srvDesc, &pTextureView
	));
}

void Texture::Bind(Graphics& gfx) noexcept {
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
