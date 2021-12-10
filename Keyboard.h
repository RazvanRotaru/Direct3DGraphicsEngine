#pragma once
#include "IODevice.h"

class Keyboard : public IODevice {
	friend class Window;
public:
	class Event {
	public:
		enum class Type {
			Press,
			Release,
			Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event() noexcept : type(Type::Invalid), code(0u) {}
		Event(Type type, unsigned char code) noexcept : type(type), code(code) {}
	public:
		bool IsPressEvent()		const noexcept { return type == Type::Press; }
		bool IsReleaseEvent()	const noexcept { return type == Type::Release; }
		bool IsInvalidEvent()	const noexcept { return type == Type::Invalid; }
		unsigned char GetCode() const noexcept { return code; }
	};
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator= (const Keyboard&) = delete;
public:
	bool IsKeyPressed(unsigned char keyCode) const noexcept;
	void Clear() noexcept;

	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool IsAutorepeatEnabled() const noexcept;
private:
	void OnKeyPressed(unsigned char keyCode) noexcept;
	void OnKeyReleased(unsigned char keyCode) noexcept;
	void OnChar(char character) noexcept;
	virtual void ClearState() noexcept override;
private:
	static constexpr unsigned int nKeys = 256u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
public:
	IODevice::Buffer<Event> keyBuffer;
	IODevice::Buffer<char> charBuffer;
};

