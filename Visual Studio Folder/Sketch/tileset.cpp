#include <exception>
#include "tileset.h"
using namespace std;

Tileset::Tileset(string fname, Uint32 w, Uint32 h):
m_sFileName(fname), m_iWidth(w), m_iHeight(h)
{
	if ( (m_pSurface = SDL_LoadBMP(m_sFileName.c_str())) == NULL) {
		throw(exception("Failed to load bitmap into Tileset"));
	}

	SDL_SetColorKey(m_pSurface, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSurface->format, 255, 0, 255));

	m_iXCount = m_pSurface->w / m_iWidth;
	m_iYCount = m_pSurface->h / m_iHeight;

	m_iCount = m_iXCount * m_iYCount;
	m_iStart = 0;
}

Tileset::~Tileset() {
	SDL_FreeSurface(m_pSurface);
}

string Tileset::GetFileName() {
	return m_sFileName;
}

SDL_Surface* Tileset::GetSurface() {
	return m_pSurface;
}

Uint32 Tileset::GetXCount() {
	return m_iXCount;
}

Uint32 Tileset::GetYCount() {
	return m_iYCount;
}

Uint32 Tileset::GetWidth() {
	return m_iWidth;
}

Uint32 Tileset::GetHeight() {
	return m_iHeight;
}

Uint32 Tileset::GetCount() {
	return m_iCount;
}

Uint32 Tileset::GetStart() {
	return m_iStart;
}

Uint32 Tileset::SetStart(Uint32 iStartIndex) {
	return m_iStart = iStartIndex;
}
