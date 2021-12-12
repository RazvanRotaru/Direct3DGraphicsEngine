#pragma once
#include "MinWindows.h"
#include "EngineException.h"
#include "DXGIInfoManager.h"
#include "GraphicsThrowMacros.h"
#include <d3d11.h>
#include <vector>
#include <wrl.h>

class Graphics {
	friend class Bindable;
public:
	class Exception : public EngineException {
		using EngineException::EngineException;
	};

	class InfoException : public Exception {
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
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
		pImmContext->ClearDepthStencilView(pDSView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
	}

	void DrawTestTriangle(float angle, float x, float y);

private:
#ifndef NDEBUG
	DXGIInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSView;
};