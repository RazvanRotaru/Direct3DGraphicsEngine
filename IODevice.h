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
		bool IsEmpty();
		void Clear();
		T ReadInput();
		void Add(T elm);
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

