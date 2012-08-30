#include <exception>
#include "colors.h"
#include "font.h"

Font::Font() {
	m_pSurface = NULL;
	m_fmt.x = m_fmt.y = m_fmt.w = m_fmt.h = 0;
}

Font::~Font() {
	Unload();
}

void Font::Load(const char* fName, SDL_Rect fmt) {
	if ( (m_pSurface = SDL_LoadBMP(fName)) == NULL) {
		throw(std::exception("Failed to load bitmap into Font"));
	}

	//check the surface matches the given format
	if (fmt.x * fmt.w != m_pSurface->w || fmt.y * fmt.h != m_pSurface->h) {
		Unload(); //picky
		throw(std::exception("Font bitmap does not match the given format"));
	}

	SDL_SetColorKey(m_pSurface, SDL_SRCCOLORKEY, MapRGB(m_pSurface->format, colors[C_HOTPINK]));

	m_fmt = fmt;
}

void Font::Unload() {
	SDL_FreeSurface(m_pSurface);
	m_pSurface = NULL;
	m_fmt.x = m_fmt.y = m_fmt.w = m_fmt.h = 0;
}

bool Font::IsLoaded() {
	if (m_pSurface == NULL) return false;
	return true;
}

void Font::DrawString(SDL_Surface* pDest, const char* str, SDL_Rect pos) {
	SDL_Rect sclip, dclip;

	sclip.w = m_fmt.w;
	sclip.h = m_fmt.h;

	for (unsigned int i = 0; i < strlen(str); i++) {
		//set sclip
		sclip.x = str[i] * m_fmt.w % m_pSurface->w;
		sclip.y = str[i] * m_fmt.w / m_pSurface->w * m_fmt.h;

		//set dclip
		dclip.x = pos.x + m_fmt.w * i;
		dclip.y = pos.y;

		SDL_BlitSurface(m_pSurface, &sclip, pDest, &dclip);
	}
}
