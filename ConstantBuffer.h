#pragma once
#include "Bindable.h"
#include "GraphicsThrowMacros.h"

template<typename C>
class ConstantBuffer : public Bindable {
public:
	ConstantBuffer(Graphics& gfx, const C& consts, UINT slot = 0u) : slot(slot) {
		INIT_INFOMNGR(gfx);

		D3D11_BUFFER_DESC cbd = {
			sizeof(consts),				// ByteWidth
			D3D11_USAGE_DYNAMIC,		// Usage
			D3D11_BIND_CONSTANT_BUFFER,	// BindFlags
			D3D11_CPU_ACCESS_WRITE,		// CPUAccessFlags
			0u,							// MiscFlags
			sizeof(C),					// StructuredByteStride
		};

		D3D11_SUBRESOURCE_DATA csd = {
			&consts,					// pSysMem
			0u,							// SysMemPitch
			0u,							// SysMemSlicePitch
		};

		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer));
	}

	ConstantBuffer(Graphics& gfx, UINT slot = 0u) : slot(slot) {
		INIT_INFOMNGR(gfx);

		D3D11_BUFFER_DESC cbd = {
			sizeof(C),					// ByteWidth
			D3D11_USAGE_DYNAMIC,		// Usage
			D3D11_BIND_CONSTANT_BUFFER,	// BindFlags
			D3D11_CPU_ACCESS_WRITE,		// CPUAccessFlags
			0u,							// MiscFlags
			0u,							// StructuredByteStride
		};
	
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&cbd, nullptr, &pConstantBuffer));
	}

	void Update(Graphics& gfx, const C& consts) {
		INIT_INFOMNGR(gfx);

		D3D11_MAPPED_SUBRESOURCE msr;
		GFX_THROW_INFO(GetContext(gfx)->Map(
			pConstantBuffer.Get(),
			0u,
			D3D11_MAP_WRITE_DISCARD,
			0u,
			&msr
		));
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	UINT slot;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C> {
	using ConstantBuffer<C>::pConstantBuffer;
	using ConstantBuffer<C>::slot;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) noexcept override {
		GetContext(gfx)->VSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C> {
	using ConstantBuffer<C>::pConstantBuffer;
	using ConstantBuffer<C>::slot;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) noexcept override {
		GetContext(gfx)->PSSetConstantBuffers(slot, 1u, pConstantBuffer.GetAddressOf());
	}
};