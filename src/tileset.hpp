#ifndef TILESET_HPP_
#define TILESET_HPP_

#include "map_tile.hpp"

#include "SDL/SDL.h"

#include <vector>

class Tileset {
public:
	Tileset() = default;
	Tileset(SDL_Surface* s, Uint16 w, Uint16 h) { SetSurface(s, w, h); }

	void DrawVectorTo(SDL_Surface* const dest, std::vector<std::vector<MapTile>>&, Sint16 x, Sint16 y);

	//accessors and mutators
	//TODO: load
	//TODO: save
	SDL_Surface* SetSurface(SDL_Surface*, Uint16 w, Uint16 h);
	SDL_Surface* GetSurface() const { return surface; };

	Uint16 GetWidth() const { return width; };
	Uint16 GetHeight() const { return height; };

private:
	SDL_Surface* surface = nullptr;
	Uint16 width = 0, height = 0;
};

#endif
