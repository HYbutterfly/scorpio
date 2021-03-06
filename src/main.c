#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "main.h"


void
open_libs(lua_State *L) {
	luaL_openlibs(L);
	luaL_requiref(L, "scorpio.core", lua_lib_core, 0);
	lua_pop(L, 1);

	luaL_requiref(L, "scorpio.serialize", lua_lib_serialize, 0);
	lua_pop(L, 1);

	luaL_requiref(L, "scorpio.socket", lua_lib_socket, 0);
	lua_pop(L, 1);

	luaL_requiref(L, "scorpio.timerfd", lua_lib_timerfd, 0);
	lua_pop(L, 1);

	luaL_requiref(L, "scorpio.epoll", lua_lib_epoll, 0);
	lua_pop(L, 1);
}


int main(int argc, char const *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "usage scorpio main.lua\n");
		return 1;
	}

	lua_State *L= luaL_newstate();

	open_libs(L);

	lua_pushboolean(L, 1);
	lua_setfield(L, LUA_REGISTRYINDEX, "main");

	int error = luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0);
	if (error) {
		fprintf(stderr, "%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}

	lua_close(L);
	return 0;
}