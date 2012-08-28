#include <exception>
#include "tileset.h"
using namespace std;

Tileset::Tileset() {
	m_pSurface = NULL;
	m_iXCount = 0;
	m_iYCount = 0;
	m_iWidth = 0;
	m_iHeight = 0;
}

Tileset::~Tileset() {
	Unload();
}

void Tileset::Load(std::string fname, Uint32 w, Uint32 h) {
	m_sFileName = fname;
	m_iWidth = w;
	m_iHeight = h;

	if ( ( m_pSurface = SDL_LoadBMP(m_sFileName.c_str()) ) == NULL) {
		Unload();
		throw(exception("Failed to load bitmap into Tileset"));
	}

	//force of habit
	SDL_SetColorKey(m_pSurface, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSurface->format, 255, 0, 255));

	m_iXCount = m_pSurface->w / m_iWidth;
	m_iYCount = m_pSurface->h / m_iHeight;
}

void Tileset::Unload() {
	SDL_FreeSurface(m_pSurface);
	m_pSurface = NULL;
	m_sFileName.clear();
	m_iXCount = 0;
	m_iYCount = 0;
	m_iWidth = 0;
	m_iHeight = 0;
}

bool Tileset::IsLoaded() {
	if (!m_pSurface) return false;
	return true;
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
	return m_iXCount * m_iYCount;
}
