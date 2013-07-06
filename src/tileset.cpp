#include "tileset.hpp"

#include <stdexcept>

void Tileset::DrawVectorTo(SDL_Surface* const dest, std::vector<std::vector<MapTile>>& tiles, Sint16 x, Sint16 y) {
	//TODO: Optimize this, so that tiles outside of the window are not shown
	if (!surface) {
		throw(std::logic_error("No tileset to draw"));
	}
	SDL_Rect sclip, dclip;
	const int xCount = surface->w / width;
	const int yCount = surface->h / height;
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			//set the clips for each tile
			sclip = {Sint16(tiles[i][j].value % xCount * width), Sint16(tiles[i][j].value / yCount * height), width, height};
			dclip = {Sint16(x + i * width), Sint16(y + j * height), width, height};
			//actually draw the damn tile
			SDL_BlitSurface(surface, &sclip, dest, &dclip);
		}
	}
}

SDL_Surface* Tileset::SetSurface(SDL_Surface* s, Uint16 w, Uint16 h) {
	width = w;
	height = h;
	return surface = s;
}
