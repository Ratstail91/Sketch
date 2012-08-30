#ifndef KR_FONT_H_
#define KR_FONT_H_

#include "SDL.h"

class Font {
public:
	Font();
	~Font();

	void Load(const char* fName, SDL_Rect fmt);
	void Unload();
	bool IsLoaded();

	void DrawString(SDL_Surface* pDest, const char* str, SDL_Rect pos);

	//OO breakers
	SDL_Surface* GetSurface() { return m_pSurface; }
	SDL_Rect* GetFormat() { return &m_fmt; }

private:
	SDL_Surface* m_pSurface;
	SDL_Rect m_fmt;
};

#endif
