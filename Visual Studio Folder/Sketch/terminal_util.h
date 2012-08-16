#ifndef KR_TERMINALUTIL_H_
#define KR_TERMINALUTIL_H_

#include "SDL.h"
#include "SDL_ttf.h"

#include "terminal.h"

void DrawTerminal(SDL_Surface* pDest, Terminal* pTerminal, TTF_Font* pFont, int iSize, SDL_Rect* pRect, unsigned int lines);

#endif
