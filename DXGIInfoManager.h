#pragma once
#include "MinWindows.h"
#include <vector>
#include <string>
#include <wrl.h>
#include <dxgidebug.h>

class DXGIInfoManager {
public:
	DXGIInfoManager();
	~DXGIInfoManager() = default;
	DXGIInfoManager(const DXGIInfoManager&) = delete;
	DXGIInfoManager& operator=(const DXGIInfoManager&) = delete;

	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
private:
	unsigned long long next = 0ull;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDXGIInfoQueue;
};

