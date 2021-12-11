#pragma once
#include "MinWindows.h"
#include "EngineException.h"
#include "DXGIInfoManager.h"
#include <d3d11.h>
#include <vector>
#include <wrl.h>

class Graphics {
public:
	class Exception : public EngineException {
		using EngineException::EngineException;
	};

	class HrException :public Exception {
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> info = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};

	class DeviceRemovedException : public HrException {
		using HrException::HrException;
	public:
		static constexpr HRESULT Code = DXGI_ERROR_DEVICE_REMOVED;
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator= (const Graphics&) = delete;
	~Graphics() = default;

	void EndFrame();

	// DEBUG only
	void ClearBuffer(float R, float G, float B) noexcept {
		const float color[] = { R,G,B,1.0f };
		pImmContext->ClearRenderTargetView(pTarget.Get(), color);
	}
private:
#ifndef NDEBUG
	DXGIInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};

#define GFX_EXCEPT_NOINFO(hr) Graphics::HrException(__LINE__, __FILE__, (hr))
#define GFX_THROW_NOINFO(hrcall) if(FAILED(hr = (hrcall))) throw Graphics::HrException(__LINE__, __FILE__, hr)

#ifndef NDEBUG
#define GFX_EXCEPT(hr) Graphics::HrException(__LINE__, __FILE__, hr, infoManager.GetMessages())
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if(FAILED(hr = (hrcall))) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__LINE__, __FILE__, (hr), infoManager.GetMessages())
#else
#define GFX_EXCEPT(hr) Graphics::HrException(__LINE__ ,__FILE__ ,(hr))
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__LINE__, __FILE__, (hr))
#endif