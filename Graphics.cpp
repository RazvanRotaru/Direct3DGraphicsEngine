#include "Graphics.h"
#include "Math.h"
#include "dxerr.h"
#include <sstream>

// TODO: remove
#include "Mesh.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace wrl = Microsoft::WRL;

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

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// for checking results of d3d functions
	HRESULT hr;

	// create device and front/back buffers, and swap chain and rendering context
	GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pImmContext
	));

	wrl::ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	GFX_THROW_INFO(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));

	// create depth-buffer
	D3D11_DEPTH_STENCIL_DESC dsDesc = {
		TRUE, // DepthEnable
		D3D11_DEPTH_WRITE_MASK_ALL, // DepthWriteMask
		D3D11_COMPARISON_LESS, // DepthFunc
		FALSE, // StencilEnable
	};

	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	GFX_THROW_INFO(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));

	// bind depth state
	pImmContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	// create depth stencil texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC dd = {
		800u,						// Width
		600u,						// Height
		1u,							// MipLevels
		1u,							// ArraySize
		DXGI_FORMAT_D32_FLOAT,		// Format
		DXGI_SAMPLE_DESC{
				1u,	// Count
				0u	// Quality
		},
		D3D11_USAGE_DEFAULT,		// Usage
		D3D11_BIND_DEPTH_STENCIL,	// BindFlags
		0u,							// CPUAccessFlags
		0u							// MiscFlags
	};
	
	GFX_THROW_INFO(pDevice->CreateTexture2D(&dd, nullptr, &pDepthStencil));

	D3D11_DEPTH_STENCIL_VIEW_DESC ddsv = {
		DXGI_FORMAT_D32_FLOAT, // Format
		D3D11_DSV_DIMENSION_TEXTURE2D, // ViewDimension
		0u, // Flags
		0u, // MipSlice
	};

	GFX_THROW_INFO(pDevice->CreateDepthStencilView(pDepthStencil.Get(), &ddsv, &pDSView));

	pImmContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSView.Get());

	// configure viewport
	D3D11_VIEWPORT vp = {
		0.0f,	// TopLeftX
		0.0f,	// TopLeftY
		800.0f, // Width
		600.0f, // Width
		0.0f,	// MinDepth
		1.0f,	// MaxDepth
	};
	pImmContext->RSSetViewports(1u, &vp);

	// init imgui d3d impl
	//ImGui_ImplDX11_Init(pDevice.Get(), pImmContext.Get());
}

void Graphics::BeginFrame(float R, float G, float B) noexcept {
	const float color[] = { R,G,B,1.0f };
	pImmContext->ClearRenderTargetView(pTarget.Get(), color);
	pImmContext->ClearDepthStencilView(pDSView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::EndFrame() {
	HRESULT hr = 0;

#ifndef NDEBUG
	infoManager.Set();
#endif // !NDEBUG

	if (FAILED(pSwapChain->Present(1u, 0u))) {
		if (hr == Graphics::DeviceRemovedException::Code) {
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		} else {
			throw GFX_EXCEPT(hr);
		}
	}
}

void Graphics::DrawIndexed(UINT count) noexcept(!IS_DEBUG) {
	GFX_THROW_INFO_ONLY(pImmContext->DrawIndexed(count, 0u, 0u));
}

void Graphics::SetCamera(DirectX::XMMATRIX view) noexcept {
	this->view = view;
}

DirectX::XMMATRIX Graphics::GetCamera() const noexcept {
	return view;
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept {
	projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept {
	return projection;
}


/****************************************************************/
/************************* EXCEPTIONS ***************************/
/****************************************************************/

Graphics::InfoException::InfoException(
	int line, const char* file,
	std::vector<std::string> infoMsgs) noexcept
	: Exception(line, file) {
	for (const auto& m : infoMsgs) {
		info += m;
		info.push_back('\n');
	}
	if (!info.empty()) { info.pop_back(); }
}


const char* Graphics::InfoException::what() const noexcept {
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\nError Info: \n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::InfoException::GetType() const noexcept {
	return "Engine Graphics Info Exception";
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept {
	return info;
}

Graphics::HrException::HrException(
	int line, const char* file, HRESULT hr,
	std::vector<std::string> info) noexcept
	: Exception(line, file), hr(hr) {

	for (const auto& m : info) {
		this->info += m;
		this->info.push_back('\n');
	}

	if (!this->info.empty()) { info.pop_back(); }
}

const char* Graphics::HrException::what() const noexcept {
	std::ostringstream oss;

	oss << GetType() << std::endl
		<< "Error Code: 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (DWORD)GetErrorCode() << ")" << std::endl
		<< "Error String: " << GetErrorString() << std::endl
		<< "Description: " << GetErrorDescription() << std::endl;

	if (!info.empty()) {
		oss << "\nError Info:\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();

	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::HrException::GetType() const noexcept {
	return "Engine Graphics Exception";
}

HRESULT Graphics::HrException::GetErrorCode() const noexcept {
	return hr;
}

std::string Graphics::HrException::GetErrorString() const noexcept {
	return DXGetErrorStringA(hr);
}

std::string Graphics::HrException::GetErrorDescription() const noexcept {
	char buf[512]{};
	DXGetErrorDescriptionA(hr, buf, sizeof(buf));
	return buf;
}

std::string Graphics::HrException::GetErrorInfo() const noexcept {
	return info;
}

const char* Graphics::DeviceRemovedException::GetType() const noexcept {
	std::ostringstream oss;

	oss << Graphics::HrException::GetType()
		<< " [Device Removed] (" << Code << ")";
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}