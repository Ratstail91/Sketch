#include "terminal_util.h"
#include "colors.h"

void DrawTerminal(SDL_Surface* pDest, Terminal* pTerminal, TTF_Font* pFont, int iSize, SDL_Rect* pRect, unsigned int lines) {
	//adjust the terminal
	while(pTerminal->GetLines()->size() > lines)
		pTerminal->GetLines()->pop_front(); //too many lines

	lines = pTerminal->GetLines()->size(); //too few lines

	//init the variables
	SDL_Rect sclip = {0, 0, pRect->w, iSize*2}, dclip = *pRect;
	SDL_Surface* pMsg = NULL;

	//fill the background
	SDL_FillRect(pDest, &dclip, SDL_MapRGB(pDest->format, colors[C_MGREY].r, colors[C_MGREY].g, colors[C_MGREY].b));

	//draw each line
	for (unsigned int i = 0; i < lines; i++) {
		//reset dclip
		dclip = *pRect;
		dclip.y += i*iSize;
		dclip.h = iSize;

		//render line
		pMsg = TTF_RenderText_Blended(pFont, pTerminal->GetLine(i).c_str(), colors[C_WHITE]);
		SDL_BlitSurface(pMsg, &sclip, pDest, &dclip);
		SDL_FreeSurface(pMsg);
	}

	//reset dclip
	dclip = *pRect;
	dclip.y += dclip.h - iSize;
	dclip.h = iSize;

	//render line
	pMsg = TTF_RenderText_Blended(pFont, pTerminal->GetInput()->c_str(), colors[C_WHITE]);
	SDL_BlitSurface(pMsg, &sclip, pDest, &dclip);
	SDL_FreeSurface(pMsg);
}