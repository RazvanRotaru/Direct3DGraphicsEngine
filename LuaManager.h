#pragma once

#include <string>
#include <iostream>
#include <stdlib.h>

extern "C"
{
#include "include\lua\include\lua.h"
#include "include\lua\include\lauxlib.h"
#include "include\lua\include\lualib.h"
}

#pragma comment(lib, "lua54.lib")

class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	static LuaManager* instance;

	void CallMethod(std::string file, std::string method) noexcept;

private:
	bool CheckError(int code);

	lua_State* L;
};

