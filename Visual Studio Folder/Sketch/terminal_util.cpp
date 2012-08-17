#include <stdexcept>
#include "terminal_util.h"
#include "colors.h"

void DrawTerminal(SDL_Surface* pDest, Terminal* pTerminal, TTF_Font* pFont, int iSize, SDL_Rect* pRect, unsigned int lines) {
	//log the lines?

	//adjust the terminal
	while(pTerminal->GetLines()->size() > lines)
		pTerminal->GetLines()->pop_front(); //too many lines

	lines = pTerminal->GetLines()->size(); //too few lines

	//init the variables
	SDL_Rect sclip = {0, 0, pRect->w, pRect->h}, dclip = *pRect;
	SDL_Surface* pMsg = NULL;

	//fill the background
	SDL_FillRect(pDest, &dclip, MapRGB(pDest->format, colors[C_DGREY] ));

	//draw each line, until out of lines
	for (unsigned int i = 0; i < lines, i < pTerminal->GetLines()->size(); i++) {
		//reset dclip
		dclip = *pRect;
		dclip.y += i*iSize;
		dclip.h = iSize;

		//render line
		pMsg = TTF_RenderText_Blended(pFont, pTerminal->GetLine(i).c_str(), colors[C_WHITE]);
		SDL_BlitSurface(pMsg, &sclip, pDest, &dclip);
		SDL_FreeSurface(pMsg);
	}

	//if there is an input string, draw it
	if (pTerminal->GetInput()->size() == 0) return;

	//reset dclip
	dclip = *pRect;
	dclip.y += dclip.h - iSize;
	dclip.h = iSize;

	//render line
	pMsg = TTF_RenderText_Blended(pFont, pTerminal->GetInput()->c_str(), colors[C_LGREY]);

	//scroll tweak
	if ( Uint16(pMsg->w) > pRect->w) {
		dclip.x -= Uint16(pMsg->w) - pRect->w;
		sclip.w += Uint16(pMsg->w) - pRect->w;
	}

	SDL_BlitSurface(pMsg, &sclip, pDest, &dclip);
	SDL_FreeSurface(pMsg);
}