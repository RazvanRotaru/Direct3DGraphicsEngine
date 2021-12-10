#pragma once
#include <queue>
#include <bitset>

class Keyboard {
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
private:
	template<typename T>
	class Buffer {
	public:
		Buffer<T>() = default;
	public:
		bool IsEmpty() { return buff.empty(); }
		void Clear() { buff = std::queue<T>(); }
		T ReadInput() {
			if (buff.size() > 0u) {
				T elm = buff.front();
				buff.pop();
				return elm;
			}
			return {};
		}
		void Add(T elm) {
			while (buff.size() > bufferSize - 1) {
				buff.pop();
			}
			buff.push(elm); 
		}
	private:
		std::queue<T> buff;
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
	void ClearState() noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autorepeatEnabled = false;
	std::bitset<nKeys> keyStates;
public:
	Buffer<Event> keyBuffer;
	Buffer<char> charBuffer;
};

