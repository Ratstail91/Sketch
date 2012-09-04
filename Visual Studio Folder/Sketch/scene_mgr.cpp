/* File Name: scene_mgr.cpp
 * Author: 
 * Date: 
 * Copyright: 
 * Description: 
*/
#include <stdexcept>
#include <iostream>

#include "SDL.h"
#include "lua.hpp"

#include "lua_util.h"

#include "colors.h"
#include "terminal.h"
#include "terminal_util.h"

#include "scene_mgr.h"

#include "region.h"
#include "tileset.h"
#include "font.h"

using namespace std;

//-------------------------
//Preprocessor directives
//-------------------------

#if KR_BASESCENEMGR_H_ != 2012062701 //27/6/2012, revision 1
#error BaseSceneMgr version is incompatible with SceneMgr
#endif

//-------------------------
//Scene headers
//-------------------------

#include "scene_editor.h"
#include "scene_tileset.h"

//-------------------------
//Public access members
//-------------------------

SceneMgr::SceneMgr() {
	m_pLuaVM = NULL;
}

//SceneMgr::~SceneMgr() {
//	//
//}

void SceneMgr::Init() {
	//init the libraries
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(-1);
	if ( (m_pLuaVM = luaL_newstate()) == NULL)
		exit(-2);

	//open the libraries
	luaL_openlibs(m_pLuaVM);

	//register the globals to lua
	SetRegister(m_pLuaVM, REG_TERMINAL, new Terminal());
	SetRegister(m_pLuaVM, REG_REGION, new Region());
	SetRegister(m_pLuaVM, REG_TILESET, new Tileset());
	SetRegister(m_pLuaVM, REG_FONT, new Font());

	try {
		//run the startup script
		DoFile(m_pLuaVM, "rsc\\scripts\\startup.lua");

		//load the font from lua (yes, it's messy)

		lua_getglobal(m_pLuaVM, "terminal");
		lua_getfield(m_pLuaVM, -1, "font");

		lua_getfield(m_pLuaVM, -1, "fname");
		lua_getfield(m_pLuaVM, -2, "x");
		lua_getfield(m_pLuaVM, -3, "y");
		lua_getfield(m_pLuaVM, -4, "w");
		lua_getfield(m_pLuaVM, -5, "h");

		SDL_Rect fmt;

		fmt.x = lua_tonumber(m_pLuaVM, -4);
		fmt.y = lua_tonumber(m_pLuaVM, -3);
		fmt.w = lua_tonumber(m_pLuaVM, -2);
		fmt.h = lua_tonumber(m_pLuaVM, -1);

		GetFont(m_pLuaVM)->Load(lua_tostring(m_pLuaVM, -5), fmt);

		lua_pop(m_pLuaVM, 7);

		//setup the screen
		lua_getglobal(m_pLuaVM, "screen");
		lua_getfield(m_pLuaVM, -1, "w");
		lua_getfield(m_pLuaVM, -2, "h");
		lua_getfield(m_pLuaVM, -3, "fullscreen");

		int w = lua_tonumber(m_pLuaVM, -3);
		int h = lua_tonumber(m_pLuaVM, -2);
		int f = lua_toboolean(m_pLuaVM, -1);

		lua_pop(m_pLuaVM, 4);

		if (w < 300 || h < 200) {
			//minimum screen size
			throw(exception("Specified screen size is too small"));
		}

		int flags = SDL_HWSURFACE|SDL_DOUBLEBUF;

		if (f) {
			flags |= SDL_FULLSCREEN;
		}

		BaseScene::SetScreen(w, h, SDL_GetVideoInfo()->vfmt->BitsPerPixel, flags);
	}
	catch(exception& e) {
		cerr << "Startup Error: " << e.what() << endl;
		TerminalPrintf(m_pLuaVM, "Error: check console");
	}

	//debugging...
	//...
}

//void SceneMgr::Proc() {
//	//
//}

void SceneMgr::Quit() {
	try {
		DoFile(m_pLuaVM, "rsc\\scripts\\shutdown.lua");
	}
	catch(exception& e) {
		cerr << "Shutdown Error: " << e.what() << endl;
		TerminalPrintf(m_pLuaVM, "Error: check console");
	}

	GetFont(m_pLuaVM)->Unload();

	//delete the pointers
	delete GetTerminal(m_pLuaVM);
	delete GetRegion(m_pLuaVM);
	delete GetTileset(m_pLuaVM);
	delete GetFont(m_pLuaVM);

	lua_close(m_pLuaVM);
	SDL_Quit();
}

//-------------------------
//Protected access members
//-------------------------

void SceneMgr::LoadScene() {
	delete GetScene();

	switch(GetNext()) {
		case BaseScene::SCENE_FIRST: //this is always the first scene in the game

		case SCENE_EDITOR:
			SetScene( new SceneEditor(m_pLuaVM) );
			break;

		case SCENE_TILESET:
			SetScene( new SceneTileset(m_pLuaVM) );
			break;
	}
}

//-------------------------
//SDL_main()
//-------------------------

#include <iostream>
using namespace std;

int SDL_main(int, char**) {
	SceneMgr app;

	app.Init();
	app.Proc();
	app.Quit();

	return 0;
}
