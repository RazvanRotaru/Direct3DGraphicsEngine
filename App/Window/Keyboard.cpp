#include "Keyboard.h"

bool Keyboard::KeyPressed(unsigned char keyCode) const noexcept {
	return keyStates[keyCode];
}

void Keyboard::Clear() noexcept {
	keyBuffer.Clear();
	charBuffer.Clear();
}

void Keyboard::EnableAutorepeat() noexcept {
	autorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept {
	autorepeatEnabled = false;
}

bool Keyboard::IsAutorepeatEnabled() const noexcept {
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keyCode) noexcept {
	keyStates[keyCode] = true;
	keyBuffer.Add(Keyboard::Event(Keyboard::Event::Type::Press, keyCode));
}

void Keyboard::OnKeyReleased(unsigned char keyCode) noexcept {
	keyStates[keyCode] = false;
	keyBuffer.Add(Keyboard::Event(Keyboard::Event::Type::Release, keyCode));
}

void Keyboard::OnChar(char chr) noexcept {
	charBuffer.Add(chr);
}

void Keyboard::ClearState() noexcept {
	keyStates.reset();
}