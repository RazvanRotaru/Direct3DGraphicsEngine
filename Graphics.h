#pragma once
#include "MinWindows.h"
#include "EngineException.h"
#include "DXGIInfoManager.h"
#include "GraphicsThrowMacros.h"
#include "Math.h"
#include <d3d11.h>
#include <vector>
#include <d3dcompiler.h>
#include <wrl.h>
#include "Camera.h"

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
	void BeginFrame(float R, float G, float B) noexcept;
	void DrawIndexed(UINT count) noexcept(!IS_DEBUG);

	void SetCamera(DirectX::XMMATRIX view) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;

	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;

private:
#ifndef NDEBUG
	DXGIInfoManager infoManager;
#endif
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pImmContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSView;
};