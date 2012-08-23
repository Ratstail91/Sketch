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
	if ( (g_pFont = TTF_OpenFont("/WINDOWS/fonts/arial.ttf", 16)) == NULL ) //platform
		exit(-5);

	//initialise lua and load the config
	luaL_openlibs(g_pLuaVM);
	luaopen_terminal(g_pLuaVM); //should be moved


	//load the tileset and the region (default layout)
	g_pTileset = new Tileset("terrain.bmp", 32, 32);
	g_pRegion = new Region(40, 40, 3);

	//set the registers
	SetRegister(g_pLuaVM, "terminal", (void*)&g_terminal);

	DoFile(g_pLuaVM, "startup.lua");

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
	DoFile(g_pLuaVM, "shutdown.lua");

	delete g_pRegion;
	delete g_pTileset;
	TTF_CloseFont(g_pFont);
	lua_close(g_pLuaVM);
	TTF_Quit();
	SDL_Quit();
}

void Draw() {
	//zero the background
	SDL_FillRect(g_pScreen, NULL, MapRGB(g_pScreen->format, colors[C_BLACK]));

	//draw the tileset
	SDL_Rect sclip, dclip;

	sclip.w = g_pTileset->GetWidth();
	sclip.h = g_pTileset->GetHeight();

	for (int i = 0; i < g_pRegion->GetXCount(); i++) {
		for (int j = 0; j < g_pRegion->GetYCount(); j++) {
			for (int k = 0; k < g_pRegion->GetLCount(); k++) {
				//set dclip
				dclip.x = i * g_pTileset->GetWidth() + g_cam.x;
				dclip.y = j * g_pTileset->GetHeight() + g_cam.y;

				//set sclip
				sclip.x = (g_pRegion->GetTile(i, j, k)-1) % g_pTileset->GetXCount() * g_pTileset->GetWidth();
				sclip.y = (g_pRegion->GetTile(i, j, k)-1) / g_pTileset->GetXCount() * g_pTileset->GetHeight();

				//blit the surface
				SDL_BlitSurface(g_pTileset->GetSurface(), &sclip, g_pScreen, &dclip);
			}
		}
	}

	//draw the terminal
	if (g_bTerminalActive) {
		SDL_Rect rect = {0, g_pScreen->h-100, g_pScreen->w, 100};
		TerminalDraw(&g_terminal, g_pScreen, g_pFont, 16, &rect, 5);
	}

	SDL_Flip(g_pScreen);
}

void MouseMotion(SDL_MouseMotionEvent const& rMotion) {
	if (rMotion.state & SDL_BUTTON_RMASK) {
		g_cam.x += rMotion.xrel;
		g_cam.y += rMotion.yrel;
	}
}

void MouseButtonDown(SDL_MouseButtonEvent const& rButton) {
	//
}

void MouseButtonUp(SDL_MouseButtonEvent const& rButton) {
	//
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
			TerminalDoString(&g_terminal, g_pLuaVM, "lua:");
		}
	}
}

void KeyUp(SDL_KeyboardEvent const& rKey) {
	if (g_bTerminalActive) {
		g_terminal.KeyUp(rKey.keysym);
	}
}
