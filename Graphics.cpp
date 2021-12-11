#include "Graphics.h"
#include "dxerr.h"
#include <sstream>
#include <d3dcompiler.h>

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

/************************* DEBUG ONLY ***************************/

void Graphics::DrawTestTriangle() {
	namespace wrl = Microsoft::WRL;

	HRESULT hr;


	// Create Internal vertex struct
	struct Vertex {
		float x;
		float y;
	};

	const Vertex vertices[] = {
		{ 0.0f, 0.5f },
		{ 0.5f, -0.5f },
		{ -0.5f, -0.5f },
	};

	// Create vertex buffer

	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;

	D3D11_BUFFER_DESC  bd = {
		sizeof(vertices),			// ByteWidth
		D3D11_USAGE_DEFAULT,		// Usage
		D3D11_BIND_VERTEX_BUFFER,	// BindFlags
		0u,							// CPUAccessFlags
		0u,							// MiscFlags
		sizeof(Vertex),				// StructuredByteStride
	};

	D3D11_SUBRESOURCE_DATA data = {
		vertices,	// pSysMem
		0u,			// SysMemPitch
		0u,			// SysMemSlicePitch
	};

	GFX_THROW_INFO(pDevice->CreateBuffer(&bd, &data, &pVertexBuffer));

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	pImmContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	// Create pixel shader
	wrl::ComPtr<ID3DBlob> pBlob;
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	GFX_THROW_INFO(D3DReadFileToBlob(TEXT("PixelShader.cso"), &pBlob));
	GFX_THROW_INFO(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	pImmContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	// Create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	GFX_THROW_INFO(D3DReadFileToBlob(TEXT("VertexShader.cso"), &pBlob));
	GFX_THROW_INFO(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));

	pImmContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);


	// create input layout
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[1] = {
		{
			"POSITION",						// SemanticName
			0u,								// SemanticIndex
			DXGI_FORMAT_R32G32_FLOAT,		// Format
			0u,								// InputSlot
			0u,								// AlignedByteOffset
			D3D11_INPUT_PER_VERTEX_DATA,	// InputSlotClass
			0u,								// InstanceDataStepRate
		}
	};

	GFX_THROW_INFO(pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout));
	pImmContext->IASetInputLayout(pInputLayout.Get());

	// bind render target
	pImmContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), nullptr);

	// set primitive topology
	pImmContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

	GFX_THROW_INFO_ONLY(pImmContext->Draw(3u, 0u));
}

/************************* DEBUG ONLY ***************************/

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