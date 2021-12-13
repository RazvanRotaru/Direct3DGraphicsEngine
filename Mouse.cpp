#include "MinWindows.h"
#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() const noexcept {
	return { x, y };
}

std::pair<int, int> Mouse::GetMouseDelta() const noexcept
{
	return { x - prevPos.first, y - prevPos.second };
}

int Mouse::GetPosX() const noexcept {
	return x;
}

int Mouse::GetPosY() const noexcept {
	return y;
}

bool Mouse::InWindow() const noexcept {
	return isInWindow;
}

bool Mouse::ButtonPressed(Button btn) const noexcept {
	return btnsState[static_cast<int>(btn)];
}

void Mouse::Clear() noexcept {
	buffer.Clear();
}

void Mouse::OnMouseMove(int x, int y) noexcept {
	this->x = x;
	this->y = y;

	buffer.Add(Mouse::Event(Mouse::Event::Type::Move, x, y));
}

void Mouse::OnMouseLeave() noexcept {
	isInWindow = false;
	buffer.Add(Mouse::Event(Mouse::Event::Type::Leave, this->x, this->y));
}

void Mouse::OnMouseEnter() noexcept {
	isInWindow = true;
	buffer.Add(Mouse::Event(Mouse::Event::Type::Enter, this->x, this->y));
}

void Mouse::ClearState() noexcept {
	btnsState.reset();
}

void Mouse::OnButtonPressed(int x, int y, Mouse::Button btn) noexcept {
	btnsState[static_cast<int>(btn)] = true;

	buffer.Add(Mouse::Event(Mouse::Event::Type::Press, x, y, btn));
}

void Mouse::OnButtonReleased(int x, int y, Mouse::Button btn) noexcept {
	btnsState[static_cast<int>(btn)] = false;

	buffer.Add(Mouse::Event(Mouse::Event::Type::Release, x, y, btn));
}

void Mouse::OnScroll(int x, int y) noexcept {
	buffer.Add(Mouse::Event(Mouse::Event::Type::Scroll, x, y));
}

void Mouse::OnScrollDelta(int x, int y, int delta) noexcept {
	wheelDeltaCarry += delta;

	// generate events for every 120 units
	while (wheelDeltaCarry >= WHEEL_DELTA) {
		wheelDeltaCarry -= WHEEL_DELTA;
		OnScroll(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA) {
		wheelDeltaCarry += WHEEL_DELTA;
		OnScroll(-x, -y);
	}
}

void Mouse::OnNewFrame() noexcept
{
	prevPos = { x, y };
}
