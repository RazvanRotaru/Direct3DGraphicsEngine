#include "Graphics.h"

#pragma comment(lib,"d3d11.lib")

Graphics::Graphics(HWND hWnd) {
	DXGI_SWAP_CHAIN_DESC sd = {
		DXGI_MODE_DESC {
			0u,	// Width
			0u,	// Height
			DXGI_RATIONAL {
				0u,	// Numerator
				0u	// Denominator
			},
			DXGI_FORMAT_R8G8B8A8_UNORM,				// Format
			DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,	// ScanlineOrdering
			DXGI_MODE_SCALING_UNSPECIFIED			// Scaling
		},
		DXGI_SAMPLE_DESC {	// No Anti-Aliasing
			1u,		// Count
			0u		// Quality
		},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,	// BufferUsage
		1u,									// BufferCount (1 front, 1 back)
		hWnd,								// OutputWindow
		TRUE,								// Windowed
		DXGI_SWAP_EFFECT_DISCARD,			// SwapEffect
		0u,									// FLAGS
	};

	D3D11CreateDeviceAndSwapChain(
		nullptr,					// pAdapter
		D3D_DRIVER_TYPE_HARDWARE,	// DriverType
		nullptr,					// Software
		0,							// Flags
		nullptr,					// pFeatureLevel
		0,							// FeatureLevels
		D3D11_SDK_VERSION,			// SDKVersion
		&sd,						// pSwapChainDesc
		&pSwapChain,						// ppSwapChain
		&pDevice,					// ppDevice
		nullptr,					// pFeatureLevel
		&pImmContext					// ppImmediateContext
	);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&pTarget
	);
	pBackBuffer->Release();
}

Graphics::~Graphics() {
	if (pDevice != nullptr) { pDevice->Release(); }
	if (pSwapChain != nullptr) { pSwapChain->Release(); }
	if (pImmContext != nullptr) { pImmContext->Release(); }
}

void Graphics::EndFrame() {
	pSwapChain->Present(1u, 0u);
}
