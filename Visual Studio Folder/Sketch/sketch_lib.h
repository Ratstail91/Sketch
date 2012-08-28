#ifndef KR_SKETCHLIB_H_
#define KR_SKETCHLIB_H_

#include "lua.h"

#define SKETCH_MAPLIBNAME "map"
LUAMOD_API int sketchopen_maplib(lua_State* L);

#define SKETCH_TILESETLIBNAME "tileset"
LUAMOD_API int sketchopen_tilesetlib(lua_State* L);

//region...

//map frame...

//tilesets...

//terminal...

#endif
