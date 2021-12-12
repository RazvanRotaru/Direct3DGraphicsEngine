#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept {
	return gfx.pImmContext.Get();
}

ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept {
	return gfx.pDevice.Get();
}

DXGIInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(IS_DEBUG) {
#ifndef NDEBUG
	return gfx.infoManager;
#else
	throw std::logic_error("tried to access gfx.infoManager in Release config");
#endif
}