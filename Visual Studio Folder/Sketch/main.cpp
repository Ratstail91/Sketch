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


static SDL_Surface* g_pScreen = NULL;
static bool g_bRunning = true;
static Terminal g_terminal;
static TTF_Font* g_pFont = NULL;
static lua_State* g_pLuaVM = NULL;


int SDL_main(int, char**) {
	//init
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(-1);
	if (TTF_Init())
		exit(-2);
	if ( (g_pLuaVM = luaL_newstate()) == NULL)
		exit(-3);

	//load
	if ( (g_pScreen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF)) == NULL)
		exit(-4);
	if ( (g_pFont = TTF_OpenFont("/WINDOWS/fonts/arial.ttf", 16)) == NULL ) //platform
		exit(-5);
	luaL_openlibs(g_pLuaVM);

	dofile(g_pLuaVM, "load.lua");


	SDL_Event event;

	while(g_bRunning) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					g_bRunning = false;
					break;

				case SDL_KEYDOWN:
					g_terminal.KeyDown(event.key.keysym);

					//run the lua code, if given the command
					if (
							//when the enter key is pressed, run the most recent line: not perfect, just proof of concept.
							event.key.keysym.sym == SDLK_RETURN &&
							g_terminal.GetLines()->size() &&
							g_terminal.GetLine(-1).size() &&
							!strncmp(g_terminal.GetLine(-1).c_str(), "lua:", 4)
						)
					{
						try {
							dostring(g_pLuaVM, g_terminal.GetLine(-1).c_str()+4);
						}
						catch(exception& e) {
							cerr << "Prompt Error: " << e.what() << endl;
						}
					}
					break;

				case SDL_KEYUP:
					g_terminal.KeyUp(event.key.keysym);
					break;
			}
		}

		//draw
		SDL_FillRect(g_pScreen, NULL, MapRGB(g_pScreen->format, colors[C_BLACK] ));

		//draw the map from lua code...

		//draw the terminal
		SDL_Rect rect = {0, 380, 640, 100};
		DrawTerminal(g_pScreen, &g_terminal, g_pFont, 16, &rect, 5);

		SDL_Flip(g_pScreen);
	}

	lua_close(g_pLuaVM);
	TTF_CloseFont(g_pFont);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
