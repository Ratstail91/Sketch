#include <iostream>
#include <stdexcept>
#include "SDL.h"
#include "SDL_ttf.h"

#include "colors.h"
#include "terminal.h"
#include "terminal_util.h"

using namespace std;


static SDL_Surface* g_pScreen = NULL;
static bool g_bRunning = true;
static Terminal g_terminal;
static TTF_Font* g_pFont = NULL;


int SDL_main(int, char**) {
	//init
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(-1);
	if (TTF_Init())
		exit(-2);

	//load
	if ( (g_pScreen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF)) == NULL)
		exit(-3);
	if ( (g_pFont = TTF_OpenFont("/WINDOWS/fonts/arial.ttf", 16)) == NULL ) //platform
		exit(-4);

	SDL_Event event;

	while(g_bRunning) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					g_bRunning = false;
					break;

				case SDL_KEYDOWN:
					g_terminal.KeyDown(event.key.keysym);
					break;

				case SDL_KEYUP:
					g_terminal.KeyUp(event.key.keysym);
					break;
			}
		}

		//draw

//		cout << g_terminal.GetLines()->size() << "::" << *g_terminal.GetInput() << endl;

		SDL_FillRect(g_pScreen, NULL, 0);

		SDL_Rect rect = {32, 32, 200, 100};

		//draw the terminal
		DrawTerminal(g_pScreen, &g_terminal, g_pFont, 16, &rect, 5);

		SDL_Flip(g_pScreen);

/*		//up...
		try {
			for (int i = 0; i < 10; i++) {
				cout << i << ": " << g_terminal.GetLine(i) << endl;
			}
		}
		catch(out_of_range) {
			cerr << "out_of_range" << endl;
		}
		catch(...) {
			cerr << "exception thrown" << endl;
		}

		cout << endl;

		//down
		try {
			for (int i = 0; i > -10; i--) {
				cout << i << ": " << g_terminal.GetLine(i) << endl;
			}
		}
		catch(out_of_range) {
			cerr << "out_of_range" << endl;
		}
		catch(...) {
			cerr << "exception thrown" << endl;
		}

		cout << endl << endl;
*/	}

	TTF_CloseFont(g_pFont);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
