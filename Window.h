#pragma once
#include "MinWindows.h"
#include "WindowThrowMacros.h"
#include "EngineException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>

class Window {
public:
	class Exception : public EngineException {
		using EngineException::EngineException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};

	class HrException : public Exception {
		using Exception::Exception;
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};

	class NoGFXException : public HrException {
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	};
public:
	class WindowException : public EngineException {
	public:
		WindowException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	class WindowClass {
	public:
		static const LPCWSTR GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator= (const WindowClass&) = delete;
	private:
		static constexpr const LPCWSTR wndClassName = L"Direct3D Engine";
		static WindowClass wndClass;
		HINSTANCE hInstance;
	};
public:
	Window(int width, int height, LPCWSTR name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void SetTitle(const std::string& title);
	static std::optional<WPARAM> ProcessMessages();
	Graphics& GFX();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandlMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};
