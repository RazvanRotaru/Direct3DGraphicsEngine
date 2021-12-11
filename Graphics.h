#pragma once
#include "MinWindows.h"
#include <d3d11.h>

class Graphics {
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator= (const Graphics&) = delete;
	~Graphics();

	void EndFrame();
	void ClearBuffer(float R, float G, float B) noexcept {
		const float color[] = { R,G,B,1.0f };
		pImmContext->ClearRenderTargetView(pTarget, color);
	}
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11DeviceContext* pImmContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};

