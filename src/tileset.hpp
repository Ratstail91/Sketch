#ifndef TILESET_HPP_
#define TILESET_HPP_

#include "SDL/SDL.h"

class Tileset {
public:
	Tileset() = default;
	Tileset(SDL_Surface* ptr, Uint16 w, Uint16 h) { SetOrigSurface(ptr, w, h); }
	~Tileset() { FreeFastSurface(); }

	void DrawTileTo(SDL_Surface* const dest, int tileIndex, Sint16 x, Sint16 y);

	//manage the various surfaces
	SDL_Surface* SetOrigSurface(SDL_Surface*, Uint16 tileWidth, Uint16 tileHeight);
	SDL_Surface* GetOrigSurface() const { return origSurface; };
	SDL_Surface* GetFastSurface() const { return fastSurface; };

	Uint16 GetWidth() const { return tileWidth; };
	Uint16 GetHeight() const { return tileHeight; };

	void FreeFastSurface();

private:
	void CreateFastSurface();
	SDL_Surface* origSurface = nullptr;
	SDL_Surface* fastSurface = nullptr;
	Uint16 tileWidth = 0, tileHeight = 0;
};

#endif
