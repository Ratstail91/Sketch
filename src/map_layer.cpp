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
#include "map_layer.hpp"

#include <stdexcept>

#define CheckRange(x, y) \
	if (x < 0 || y < 0 || x >= tiles.size() || y >= tiles.begin()->size()) \
		throw(std::out_of_range("tile index out of range"));


void MapLayer::Generate(int width, int height, tile_t defaultValue) {
	if (width <= 0) {
		throw(std::invalid_argument("Cannot generate less than one column of tiles"));
	}
	if (height <= 0) {
		throw(std::invalid_argument("Cannot generate less than one row of tiles"));
	}

	tiles.clear();

	/* 1. create a vector<vector<MapTile>> structure of size "width"
	 * 2. create a vector<MapTile> structure of size "height", which is the default value for above
	 * 3. create a MapTile structure with the value "defaultValue", which is the default value for above
	 * 4. cast is as an rvalue to prevent expensive movement
	*/
	using std::vector;
	tiles = std::move(vector<vector<MapTile>>(width, vector<MapTile>(height, MapTile{defaultValue})));
}

void MapLayer::Clear() {
	tiles.clear();
}

void MapLayer::DrawTo(SDL_Surface* const dest, Tileset* tset, int x, int y) {
	tset->DrawVectorTo(dest, tiles, x, y);
}

tile_t MapLayer::SetTile(int x, int y, tile_t value) {
	CheckRange(x, y);
	return tiles[x][y].value = value;
}

tile_t MapLayer::GetTile(int x, int y) {
	CheckRange(x, y);
	return tiles[x][y].value;
}
