#include "Sampler.h"
#include "GraphicsThrowMacros.h"

Sampler::Sampler(Graphics& gfx) {
	INIT_INFOMNGR(gfx);

	D3D11_SAMPLER_DESC desc = {
		D3D11_FILTER_MIN_MAG_MIP_POINT,	// Filter
		D3D11_TEXTURE_ADDRESS_WRAP,		//AddressU
		D3D11_TEXTURE_ADDRESS_WRAP,		//AddressV
		D3D11_TEXTURE_ADDRESS_WRAP		//AddressW
	};

	GFX_THROW_INFO(GetDevice(gfx)->CreateSamplerState(&desc, &pSampler));
}

void Sampler::Bind(Graphics& gfx) noexcept {
	GetContext(gfx)->PSSetSamplers(0u, 1u, pSampler.GetAddressOf());
}
