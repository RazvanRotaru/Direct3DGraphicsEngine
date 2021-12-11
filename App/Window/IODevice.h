#pragma once
#include <queue>
#include <bitset>

class IODevice {
	friend class Window;
protected:
	template<typename T>
	class Buffer {
	public:
		Buffer<T>() = default;
	public:
		bool IsEmpty() {
			return buff.empty();
		}
		void Clear() {
			buff = std::queue<T>();
		}
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
	IODevice() = default;
	IODevice(const IODevice&) = delete;
	IODevice& operator= (const IODevice&) = delete;
public:
	virtual void ClearState() noexcept = 0;
private:
	static constexpr unsigned int bufferSize = 16u;
};

