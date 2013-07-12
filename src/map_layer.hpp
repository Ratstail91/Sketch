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
#ifndef MAPLAYER_HPP_
#define MAPLAYER_HPP_

#include "map_tile.hpp"
#include "tileset.hpp"

#include "SDL/SDL.h"

#include <vector>

class MapLayer {
public:
	MapLayer() = default;
	MapLayer(int w, int h, TILE_TYPE v) { Generate(w, h, v); }

	void Generate(int width, int height, TILE_TYPE defaultValue);
	void Clear();

	void DrawTo(SDL_Surface* const, Tileset*, int x, int y);

	//accessors and mutators
	TILE_TYPE SetTile(int x, int y, TILE_TYPE value);
	TILE_TYPE GetTile(int x, int y);

	int GetWidth() const { return tiles.size(); }
	int GetHeight() const { return tiles.size() ? tiles.begin()->size() : 0; }

private:
	std::vector<std::vector<MapTile>> tiles;
};

#endif
