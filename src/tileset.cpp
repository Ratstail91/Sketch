#include "tileset.hpp"

#include <stdexcept>

void Tileset::DrawTileTo(SDL_Surface* const dest, int tileIndex, Sint16 x, Sint16 y) {
	if (tileIndex < 0) {
		return;
	}
	SDL_Rect dclip = {x, y, tileWidth, tileHeight};
	SDL_Rect sclip = {Sint16(x * tileIndex), 0, tileWidth, tileHeight};
	SDL_BlitSurface(fastSurface, &sclip, dest, &dclip);
}

SDL_Surface* Tileset::SetOrigSurface(SDL_Surface* s, Uint16 w, Uint16 h) {
	origSurface = s;
	tileWidth = w;
	tileHeight = h;
	FreeFastSurface();
	CreateFastSurface();
	return origSurface;
}

void Tileset::FreeFastSurface() {
	SDL_FreeSurface(fastSurface);
	fastSurface = nullptr;
}

void Tileset::CreateFastSurface() {
	if (!origSurface) {
		throw(std::runtime_error("Can't create a fast tile surface, no original surface received"));
	}

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	constexpr Uint32 rmask = 0xff000000;
	constexpr Uint32 gmask = 0x00ff0000;
	constexpr Uint32 bmask = 0x0000ff00;
	constexpr Uint32 amask = 0x000000ff;
#else
	constexpr Uint32 rmask = 0x000000ff;
	constexpr Uint32 gmask = 0x0000ff00;
	constexpr Uint32 bmask = 0x00ff0000;
	constexpr Uint32 amask = 0xff000000;
#endif

	//the number of tiles in the tileset
	int setWidth = origSurface->w / tileWidth;
	int setHeight = origSurface->h / tileHeight;

	fastSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, setWidth * setHeight * tileWidth, tileHeight, 32, rmask, gmask, bmask, amask);

	if (!fastSurface) {
		throw(std::runtime_error("Failed to create the fast tileset surface"));
	}

	//blit the original surface to the fast one
	for (int i = 0; i < setHeight; i++) {
		SDL_Rect sclip = {0, Sint16(i * tileHeight), Uint16(tileWidth * setWidth), tileHeight};
		SDL_Rect dclip = {Sint16(i * tileWidth * setWidth), 0, Uint16(tileWidth * setWidth), tileHeight};
		SDL_BlitSurface(origSurface, &sclip, fastSurface, &dclip);
	}
}
