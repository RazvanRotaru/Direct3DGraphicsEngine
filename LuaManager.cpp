#include "LuaManager.h"

LuaManager* LuaManager::instance = nullptr;

LuaManager::LuaManager()
{
	L = luaL_newstate();

	if (instance == nullptr) {
		luaL_openlibs(L);
		instance = this;
	} else {
		delete this;
	}
}

LuaManager::~LuaManager()
{
	system("pause");
	lua_close(L);
}

void LuaManager::CallMethod(std::string file, std::string method) noexcept
{
	if (!CheckError(luaL_dofile(L, file.c_str()))) return;

	lua_getglobal(L, method.c_str());
	if (lua_isfunction(L, -1)) {
		if (!CheckError(lua_pcall(L, 0, 0, 0))) return;
	}
}

bool LuaManager::CheckError(int code)
{
	if (code != LUA_OK) {
		std::string errMsg = lua_tostring(L, -1);
		std::cout << errMsg << std::endl;
		return false;
	}

	return true;
}
