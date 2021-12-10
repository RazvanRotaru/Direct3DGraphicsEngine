#include "IODevice.h"

template<typename T>
bool IODevice::Buffer<T>::IsEmpty() {
	return buff.empty();
}

template<typename T>
void IODevice::Buffer<T>::Clear() {
	buff = std::queue<T>();
}

template<typename T>
T IODevice::Buffer<T>::ReadInput() {
	if (buff.size() > 0u) {
		T elm = buff.front();
		buff.pop();
		return elm;
	}
	return {};
}

template<typename T>
void IODevice::Buffer<T>::Add(T elm) {
	while (buff.size() > bufferSize - 1) {
		buff.pop();
	}
	buff.push(elm);
}

