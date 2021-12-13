#pragma once
#include "IODevice.h"

class Mouse : public IODevice {
	friend class Window;
public:
	enum class Button {
		Left = 0,
		Right = 1,
		None,
	};

	class Event {
	public:
		enum class Type {
			Press,
			Release,
			Scroll,
			Move,
			Enter,
			Leave,
			Invalid,
		};
	private:
		Type type;
		Mouse::Button btn;
		int x;
		int y;
	public:
		Event() noexcept : type(Type::Invalid), btn(Mouse::Button::None), x(0), y(0) {}
		Event(Type type, int x, int y,
			  const Mouse::Button btn = Mouse::Button::None)
			noexcept : type(type), btn(btn), x(x), y(y) {
		}
		Type GetType() const noexcept { return type; }
		std::pair<int, int> GetPos() const noexcept { return { x,y }; }
		int GetPosX() const noexcept { return x; }
		int GetPosY() const noexcept { return y; }
		Mouse::Button GetButton() const noexcept { return btn; }
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	
	std::pair<int, int> GetPos() const noexcept;
	std::pair<int, int> GetMouseDelta() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	
	bool InWindow() const noexcept;
	bool ButtonPressed(Button btn) const noexcept;
	void OnNewFrame() noexcept;

	void Clear() noexcept;
private:
	void OnMouseMove(int x, int y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnButtonPressed(int x, int y, Button btn) noexcept;
	void OnButtonReleased(int x, int y, Button btn) noexcept;
	void OnScroll(int x, int y) noexcept;
	void OnScrollDelta(int x, int y, int delta) noexcept;
	virtual void ClearState() noexcept override;
private:
	static constexpr unsigned int nKeys = 2u;
	std::bitset<nKeys> btnsState;
	bool isInWindow = false;
	int wheelDeltaCarry = 0;
	int x = 0, y = 0;
	mutable std::pair<int, int> prevPos = {0, 0};
public:
	IODevice::Buffer<Event> buffer;
};