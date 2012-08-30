//Although this is a "one page main" system, I'll probably change this later


//preprocessor directives
#include <iostream>
#include <stdexcept>

#include "SDL.h"
#include "SDL_ttf.h"
#include "lua.hpp"

#include "lua_util.h"

#include "colors.h"
#include "terminal.h"
#include "terminal_util.h"

using namespace std;


#include "region.h"
#include "tileset.h"


//globals
static SDL_Surface* g_pScreen = NULL;
static bool g_bRunning = true;
static Terminal g_terminal;
static TTF_Font* g_pFont = NULL;
static lua_State* g_pLuaVM = NULL;
static bool g_bTerminalActive = true;
static SDL_Rect g_cam = {0, 0};


//forward declarations
void Init();
void Proc();
void Quit();
void Draw();

void MouseMotion		(SDL_MouseMotionEvent const&);
void MouseButtonDown	(SDL_MouseButtonEvent const&);
void MouseButtonUp		(SDL_MouseButtonEvent const&);
void KeyDown			(SDL_KeyboardEvent const&);
void KeyUp				(SDL_KeyboardEvent const&);


//entry point
int SDL_main(int, char**) {
	try {
		Init();
		Proc();
		Quit();
	}
	catch(exception& e) {
		cerr << "Error: " << e.what() << endl;
	}

	return 0;
}


//function definitions
void Init() {
	//init
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(-1);
	if (TTF_Init())
		exit(-2);
	if ( (g_pLuaVM = luaL_newstate()) == NULL)
		exit(-3);

	//load
	if ( (g_pScreen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE|SDL_DOUBLEBUF)) == NULL)
		exit(-4);
	if ( (g_pFont = TTF_OpenFont("/WINDOWS/fonts/arial.ttf", 16)) == NULL ) //platform dependancy
		exit(-5);

	//initialise lua and load the config
	luaL_openlibs(g_pLuaVM);

	//register the globals for lua
	SetRegister(g_pLuaVM, REG_TERMINAL, &g_terminal);
	SetRegister(g_pLuaVM, REG_REGION, new Region());
	SetRegister(g_pLuaVM, REG_TILESET, new Tileset());

	try {
		DoFile(g_pLuaVM, "startup.lua");
	}
	catch(exception& e) {
		cerr << "Startup Error: " << e.what() << endl;
		TerminalPrintf(&g_terminal, "Error: check console");
	}

	//debugging...
	//...
}

void Proc() {
	SDL_Event event;

	while(g_bRunning) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					g_bRunning = false;
					break;

				case SDL_MOUSEMOTION:
					MouseMotion(event.motion);
					break;

				case SDL_MOUSEBUTTONDOWN:
					MouseButtonDown(event.button);
					break;

				case SDL_MOUSEBUTTONUP:
					MouseButtonUp(event.button);
					break;

				case SDL_KEYDOWN:
					KeyDown(event.key);
					break;

				case SDL_KEYUP:
					KeyUp(event.key);
					break;

				//etc.
			}
		}
		Draw();
	}
}

void Quit() {
	try {
		DoFile(g_pLuaVM, "shutdown.lua");
	}
	catch(exception& e) {
		cerr << "Shutdown Error: " << e.what() << endl;
		TerminalPrintf(&g_terminal, "Error: check console");
	}

	//delete the pointers
	delete GetRegisterUserData(g_pLuaVM, REG_REGION);
	delete GetRegisterUserData(g_pLuaVM, REG_TILESET);

	TTF_CloseFont(g_pFont);
	lua_close(g_pLuaVM);
	TTF_Quit();
	SDL_Quit();
}

void Draw() {
	//this could be pushed into a script...

	//zero the background
	SDL_FillRect(g_pScreen, NULL, MapRGB(g_pScreen->format, colors[C_BLACK]));

	//draw the map
	Region* pRegion = (Region*)GetRegisterUserData(g_pLuaVM, REG_REGION);
	Tileset* pTileset = (Tileset*)GetRegisterUserData(g_pLuaVM, REG_TILESET);

	if (pRegion->IsLoaded() && pTileset->IsLoaded()) {
		SDL_Rect sclip, dclip;

		//setup sclip
		sclip.w = pTileset->GetWidth();
		sclip.h = pTileset->GetHeight();

		for (int i = 0; i < pRegion->GetXCount(); i++) {
			for (int j = 0; j < pRegion->GetYCount(); j++) {
				for (int k = 0; k < pRegion->GetLCount(); k++) {
					//set dclip
					dclip.x = i * pTileset->GetWidth() + g_cam.x;
					dclip.y = j * pTileset->GetHeight() + g_cam.y;

					//set sclip
					sclip.x = (pRegion->GetTile(i, j, k)-1) % pTileset->GetXCount() * pTileset->GetWidth();
					sclip.y = (pRegion->GetTile(i, j, k)-1) / pTileset->GetXCount() * pTileset->GetHeight();

					//blit the surface
					SDL_BlitSurface(pTileset->GetSurface(), &sclip, g_pScreen, &dclip);
				}//l
			}//y
		}//x
	}//if

	//draw the terminal
	if (g_bTerminalActive) {
		SDL_Rect rect = {0, g_pScreen->h-100, g_pScreen->w, 100};
		TerminalDraw(&g_terminal, g_pScreen, &rect, g_pFont, 16, 5);
	}

	SDL_Flip(g_pScreen);
}

void MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	if (rMotion.state & SDL_BUTTON_RMASK) {
		g_cam.x += rMotion.xrel;
		g_cam.y += rMotion.yrel;
	}

	try {
		//run the brush script
		lua_getglobal(g_pLuaVM, "brush");
		lua_getfield(g_pLuaVM, -1, "active");
		lua_getfield(g_pLuaVM, -1, "mousemotion");
		lua_pushnumber(g_pLuaVM, rMotion.state);
		lua_pushnumber(g_pLuaVM, rMotion.x-g_cam.x);
		lua_pushnumber(g_pLuaVM, rMotion.y-g_cam.y);
		lua_pushnumber(g_pLuaVM, rMotion.xrel);
		lua_pushnumber(g_pLuaVM, rMotion.yrel);
		lua_pcall(g_pLuaVM, 5, 0, 0);
		lua_pop(g_pLuaVM, 2);
	}
	catch(exception& e) {
		cout << "Brush Error: " << e.what() << endl;
	}
}

void MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		lua_getglobal(g_pLuaVM, "brush");
		lua_getfield(g_pLuaVM, -1, "active");
		lua_getfield(g_pLuaVM, -1, "mousebuttondown");
		lua_pushnumber(g_pLuaVM, rButton.button);
		lua_pushnumber(g_pLuaVM, rButton.x-g_cam.x);
		lua_pushnumber(g_pLuaVM, rButton.y-g_cam.y);
		lua_pcall(g_pLuaVM, 3, 0, 0);
		lua_pop(g_pLuaVM, 2);
	}
	catch(exception& e) {
		cout << "Brush Error: " << e.what() << endl;
	}
}

void MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	try {
		//run the brush script
		lua_getglobal(g_pLuaVM, "brush");
		lua_getfield(g_pLuaVM, -1, "active");
		lua_getfield(g_pLuaVM, -1, "mousebuttonup");
		lua_pushnumber(g_pLuaVM, rButton.button);
		lua_pushnumber(g_pLuaVM, rButton.x-g_cam.x);
		lua_pushnumber(g_pLuaVM, rButton.y-g_cam.y);
		lua_pcall(g_pLuaVM, 3, 0, 0);
		lua_pop(g_pLuaVM, 2);
	}
	catch(exception& e) {
		cout << "Brush Error: " << e.what() << endl;
	}
}

void KeyDown(SDL_KeyboardEvent const& rKey) {
	switch(rKey.keysym.sym) {
		case SDLK_ESCAPE:
			if (!g_bTerminalActive) {
				g_bRunning = false;
			}
			break;

		case SDLK_TAB:
			g_bTerminalActive = !g_bTerminalActive;
			return; //prevent the terminal from picking up this key
	}

	if (g_bTerminalActive) {
		g_terminal.KeyDown(rKey.keysym);

		if (rKey.keysym.sym == SDLK_RETURN) {
			TerminalDoString(&g_terminal, g_pLuaVM);
		}
	}
}

void KeyUp(SDL_KeyboardEvent const& rKey) {
	if (g_bTerminalActive) {
		g_terminal.KeyUp(rKey.keysym);
	}
}
