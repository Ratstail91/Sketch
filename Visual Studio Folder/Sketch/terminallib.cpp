#include <exception>
#include "lua.hpp"
#include "lua_util.h"
#include "sketch_lib.h"

#include "terminal.h"

//preprocessor

#define CHECK_LTHAN(L, i) if (lua_gettop(L) < i) throw(std::exception("Too few arguments"));
#define CHECK_GTHAN(L, i) if (lua_gettop(L) > i) throw(std::exception("Too many arguments"));

//glue functions
int terminal_Push(lua_State* L) {
	//push to the terminal, one line at a time

	const char* str = NULL;
	int argc = lua_gettop(L);

	for (int i = 0; i < argc; i++) {
		if ( (str = lua_tostring(L,-argc+i)) == NULL) {
			throw(std::exception("Failed to push line to the terminal"));
		}

		reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->Push(str);
	}

	return 0;
}

int terminal_Print(lua_State* L) {
	//print to the terminal

	std::string s;
	int argc = lua_gettop(L);

	for (int i = 0; i < argc; i++) {
		s += lua_tostring(L,-argc+i);
		s += "    ";
	}

	reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->Push(s);

	return 0;
}

int terminal_GetLine(lua_State* L) {
	CHECK_LTHAN(L, 1);
	CHECK_GTHAN(L, 1);

	double line = lua_tonumber(L, 1);

	if (line < 0) line++; //compensate for reading from both directions

	std::string s = reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetLine(line-1);

	lua_pushstring(L, s.c_str());

	return 1;
}

int terminal_GetLineCount(lua_State* L) {
	double ret = reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetLines()->size();
	lua_pushnumber(L, ret);
	return 1;
}

int terminal_PopLine(lua_State* L) {
	CHECK_GTHAN(L, 0);
	reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetLines()->pop_back();
	return 0;
}

int terminal_ClearLines(lua_State* L) {
	CHECK_GTHAN(L, 0);
	reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetLines()->clear();
	return 0;
}

int terminal_GetInput(lua_State* L) {
	CHECK_GTHAN(L, 0);
	std::string s = *(reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetInput());
	lua_pushstring(L, s.c_str());
	return 1;
}

int terminal_SetInput(lua_State* L) {
	CHECK_LTHAN(L, 1);
	CHECK_GTHAN(L, 1);

	const char* str = lua_tostring(L, 1);
	*(reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetInput()) = str;

	return 0;
}

int terminal_ClearInput(lua_State* L) {
	CHECK_GTHAN(L, 0);
	reinterpret_cast<Terminal*>(GetRegisterUserData(L, REG_TERMINAL))->GetInput()->clear();
	return 0;
}

//library
static const luaL_Reg terminallib[] = {
	{"push", terminal_Push},
	{"print", terminal_Print},
	{"get", terminal_GetLine},
	{"count", terminal_GetLineCount},
	{"pop", terminal_PopLine},
	{"clear", terminal_ClearLines},
	{"getinput", terminal_GetInput},
	{"setinput", terminal_SetInput},
	{"clearinput", terminal_ClearInput},
	{NULL, NULL},
};

int sketchopen_terminallib(lua_State* L) {
	luaL_newlib(L, terminallib);
	return 1;
}
