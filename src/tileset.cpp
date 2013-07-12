/* Copyright: (c) Kayne Ruse 2013
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "tileset.hpp"

#include <stdexcept>

void Tileset::DrawTileTo(SDL_Surface* const dest, tile_t index, Sint16 x, Sint16 y) {
	if (!surface) {
		throw(std::logic_error("No tileset to draw"));
	}
	if (index == TILE_NONE) {
		return;
	}

	SDL_Rect sclip = {Sint16(index % (surface->w/width) * width), Sint16(index / (surface->w/width) * height), width, height};
	SDL_Rect dclip = {x, y, width, height};
	SDL_BlitSurface(surface, &sclip, dest, &dclip);
}

void Tileset::DrawVectorTo(SDL_Surface* const dest, std::vector<std::vector<MapTile>>& tiles, Sint16 x, Sint16 y) {
	if (!surface) {
		throw(std::logic_error("No tileset to draw"));
	}

	//these are the clipping rectangles
	SDL_Rect sclip = {0, 0, width, height};
	SDL_Rect dclip = {0, 0, width, height};

	/* create these constant integers to help clear up the code
	 * and to reduce the number of calculations per call (and possible bugs)
	*/

	//number of tiles on the tilesheet (could cache these)
	const int xCount = surface->w / width;
	const int yCount = surface->h / height;

	//start & end positions of the nested loops, skipping tiles not on the screen
	const int iStart = std::max(-x/width, 0);
	const int iEnd = std::min((-x + dest->w)/width + 1, int(tiles.size()));
	const int jStart = std::max(-y/height, 0);
	const int jEnd = std::min((-y + dest->h)/height + 1, tiles.size() ? int(tiles.begin()->size()) : 0);

	//iterate through the matrix
	for (int i = iStart; i < iEnd; i++) {
		for (int j = jStart; j < jEnd; j++) {
			//skip invisible tiles
			if (tiles[i][j].value == TILE_NONE) {
				continue;
			}

			//set the clips for each tile
			sclip.x = Sint16(tiles[i][j].value % xCount * width);
			sclip.y = Sint16(tiles[i][j].value / xCount * height);
			dclip.x = Sint16(x + i * width);
			dclip.y = Sint16(y + j * height);

			//use a copy because of SDL overriding the w & h fields
			SDL_Rect dup = dclip;

			//actually draw the damn tile
			SDL_BlitSurface(surface, &sclip, dest, &dup);
		}
	}
}

void Tileset::LoadSurface(std::string s, Uint16 w, Uint16 h) {
	//should there be a warning here for when a surface has more tiles than TILE_MAX?
	FreeSurface();
	if (!(surface = SDL_LoadBMP(s.c_str()))) {
		throw(std::runtime_error(std::string() + "Failed to load tileset: " + s));
	}
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 255, 0, 255));
	width = w;
	height = h;
	fileName = s;
}

void Tileset::FreeSurface() {
	SDL_FreeSurface(surface);
	surface = nullptr;
}

SDL_Surface* Tileset::SetSurface(SDL_Surface* s, Uint16 w, Uint16 h) {
	width = w;
	height = h;
	return surface = s;
}
