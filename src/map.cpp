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
#include "map.hpp"

#include <stdexcept>

//define the singleton instance
Map Map::singleton;

//bah, this is a crappy shortcut, but it works
#define CheckVecRange(vec, idx) \
	if (idx < 0 || idx >= vec.size()) { throw(std::out_of_range("layer index out of range")); }


void Map::Generate(int l, int w, int h, tile_t v) {
	if (l <= 0) {
		throw(std::invalid_argument("Cannot generate less than one layer of tiles"));
	}

	layers.clear();
	layers.reserve(l);
	MapLayer tmp;
	tmp.Generate(w, h, v);
	for (int i = 0; i < l; i++) {
		//implicitly calls the copy constructor
		layers.push_back(tmp);
	}
}

void Map::Clear() {
	layers.clear();
}

void Map::DrawLayerTo(SDL_Surface* const dest, Tileset* tset, int l, int x, int y) {
	CheckVecRange(layers, l);
	layers[l].DrawTo(dest, tset, x, y);
}

void Map::InsertLayer(int l, tile_t dv) {
	if (layers.size() == 0) {
		throw(std::logic_error("Cannot insert into an empty map"));
	}

	//don't use the macro, since this condition is slightly different
	if (l < 0 || l > layers.size()) {
		throw(std::out_of_range("layer index out of range"));
	}

	MapLayer ml(layers.begin()->GetWidth(), layers.begin()->GetHeight(), dv);
	layers.insert(layers.begin()+l, ml);
}

void Map::DeleteLayer(int l) {
	//can't delete the last layer
	if (layers.size() == 1) {
		throw(std::logic_error("Cannot delete the last layer of the map"));
	}

	CheckVecRange(layers, l);
	layers.erase(layers.begin()+l);
}

tile_t Map::SetTile(int l, int x, int y, tile_t v) {
	CheckVecRange(layers, l);
	return layers[l].SetTile(x, y, v);
}

tile_t Map::GetTile(int l, int x, int y) {
	CheckVecRange(layers, l);
	return layers[l].GetTile(x, y);
}

MapLayer* Map::GetLayer(int l) {
	CheckVecRange(layers, l);
	return &layers[l];
}
