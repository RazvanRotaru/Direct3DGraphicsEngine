#include "EngineException.h"
#include <sstream>

EngineException::EngineException(int line, const char* file) noexcept : line(line), file(file) {}

const char* EngineException::what() const noexcept {
	std::ostringstream oss;
	oss << "\033[" << GetType() << "m" << std::endl
		<< "\033[" << GetOriginString() << "m";

	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* EngineException::GetType() const noexcept {
	return "EngineException";
}

int EngineException::GetLine() const noexcept {
	return line;
}

const std::string& EngineException::GetFile() const noexcept {
	return file;
}

std::string EngineException::GetOriginString() const noexcept {
	std::ostringstream oss;
	oss << "File: \033[" << file << "m" << std::endl
		<< "Line: \033[" << line << "m";
	return oss.str();
}
