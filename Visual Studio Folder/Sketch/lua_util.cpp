#define _CRT_SECURE_NO_WARNINGS //I'm really sick of your shit VC++!
#include <exception>
#include <iostream>
#include <stdarg.h>

#include "lua.hpp"
#include "lua_util.h"

using namespace std;

void Error(lua_State* L, const char* fmt, ...) {
	//get the formatted string
	va_list argp;

	va_start(argp, fmt);

	char buf[1024];
	vsprintf(buf, fmt, argp);

	va_end(argp);

	//clear the lua stack
	while(!lua_isnil(L, -1)) lua_pop(L, 1);

	//throw this error as an exception
	throw(exception(buf));
}

void DoFile(lua_State* L, const char* fname) {
	if (luaL_loadfile(L, fname) || lua_pcall(L, 0,0,0)) {
		Error(L, "Cannot run the specified file: %s", lua_tostring(L, -1));
	}
}

void DoString(lua_State* L, const char* str) {
	if (luaL_loadbuffer(L, str, strlen(str), "line") || lua_pcall(L, 0,0,0)) {
		Error(L, "Cannot run the specified string: %s", lua_tostring(L, -1));
	}
}

void DoCall(lua_State* L, const char* func, const char* sig, ...) {
	va_list vl;
	int narg, nres; //number of args & results

	va_start(vl, sig);
	lua_getglobal(L, func);

	//push arguments
	narg = 0;
	while(*sig) {
		switch(*sig++) {
			case 'd': lua_pushnumber(L, va_arg(vl, double)); break;
			case 'i': lua_pushnumber(L, va_arg(vl, int)); break;
			case 's': lua_pushstring(L, va_arg(vl, char*)); break;
			case '>': goto endwhile; //omg
			default: Error(L, "invalid option (%c)\n", *(sig-1));
		}

		narg++;
		luaL_checkstack(L, 1, "too many arguments"); //expand the stack
	}endwhile: //eww

	//call
	nres = strlen(sig);
	if (lua_pcall(L, narg, nres, 0)) {
		Error(L, "Error running function %s", lua_tostring(L, -1));
	}

	//retieve the results
	nres = -nres; //stack pos of the first result
	while(*sig) {
		switch(*sig++) {
			case 'd':
				if (!lua_isnumber(L, nres)) Error(L, "wrong result type");
				*va_arg(vl, double*) = lua_tonumber(L, nres); //these va args are passed as pointers
				break;

			case 'i':
				if (!lua_isnumber(L, nres)) Error(L, "wrong result type");
				*va_arg(vl, int*) = (int)lua_tonumber(L, nres);
				break;

			case 's':
				if (!lua_isstring(L, nres)) Error(L, "wrong result type");
				*va_arg(vl, const char **) = lua_tostring(L, nres);
				break;

			default:
				Error(L, "invalid option(%c)\n", *(sig-1));
		}
		nres++;
	}
	va_end(vl);
}

void SetRegister(lua_State* L, const char* key, void* udata) {
	lua_pushstring(L, key);
	lua_pushlightuserdata(L, udata);
	lua_settable(L, LUA_REGISTRYINDEX);
}

void PushRegister(lua_State* L, const char* key) {
	lua_pushstring(L, key);
	lua_gettable(L, LUA_REGISTRYINDEX);
}

void* GetRegisterUserData(lua_State* L, const char* key) {
	PushRegister(L, key);
	void* p = lua_touserdata(L, -1);
	lua_pop(L, 1);
	return p;
}
