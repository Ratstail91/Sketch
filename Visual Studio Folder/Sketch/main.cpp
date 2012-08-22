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
static Tileset* g_pTileset = NULL;
static Region* g_pRegion = NULL;


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
	if ( (g_pFont = TTF_OpenFont("/WINDOWS/fonts/arial.ttf", 16)) == NULL ) //platform
		exit(-5);

	//initialise lua and load the config
	luaL_openlibs(g_pLuaVM);
	lua_TerminalOpen(g_pLuaVM, &g_terminal); //should be moved


	//load the tileset and the region (default layout)
	g_pTileset = new Tileset("terrain.bmp", 32, 32);
	g_pRegion = new Region(40, 40, 3);

	DoFile(g_pLuaVM, "startup.lua");
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
	DoFile(g_pLuaVM, "shutdown.lua");

	delete g_pRegion;
	delete g_pTileset;
	TTF_CloseFont(g_pFont);
	lua_close(g_pLuaVM);
	TTF_Quit();
	SDL_Quit();
}

void Draw() {
	SDL_FillRect(g_pScreen, NULL, MapRGB(g_pScreen->format, colors[C_BLACK]));

	SDL_BlitSurface(g_pTileset->GetSurface(), NULL, g_pScreen, NULL);

	//draw the terminal
	SDL_Rect rect = {0, g_pScreen->h-100, g_pScreen->w, 100};
	TerminalDraw(&g_terminal, g_pScreen, g_pFont, 16, &rect, 5);

	SDL_Flip(g_pScreen);
}

void MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	//
}

void MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	//
}

void MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	//
}

void KeyDown(SDL_KeyboardEvent const& rKey) {
	g_terminal.KeyDown(rKey.keysym);

	if (rKey.keysym.sym == SDLK_RETURN) {
		TerminalDoString(&g_terminal, g_pLuaVM, "lua:");
	}
}

void KeyUp(SDL_KeyboardEvent const& rKey) {
	g_terminal.KeyUp(rKey.keysym);
}
