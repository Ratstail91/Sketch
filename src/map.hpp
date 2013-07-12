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
#ifndef MAP_HPP_
#define MAP_HPP_

#include "map_layer.hpp"
#include "tileset.hpp"

#include "SDL/SDL.h"

#include <vector>

class Map {
public:
	//singleton pattern
	static Map* GetSingletonPtr() { return &singleton; }
	static Map& GetSingletonRef() { return singleton; };

	void Generate(int layerCount, int width, int height, tile_t defaultValue = TILE_NONE);
	void Clear();

	void DrawLayerTo(SDL_Surface* const, Tileset*, int layer, int x, int y);

	//accessors and mutators
	void InsertLayer(int layer, tile_t defaultValue = TILE_NONE);
	void DeleteLayer(int layer);

	tile_t SetTile(int l, int x, int y, tile_t value);
	tile_t GetTile(int l, int x, int y);

	MapLayer* GetLayer(int l);

	int GetLayerCount() const { return layers.size(); }
	int GetWidth() const { return layers.size() ? layers.begin()->GetWidth() : 0; }
	int GetHeight() const { return layers.size() ? layers.begin()->GetHeight() : 0; }

private:
	//singleton pattern
	Map() = default;
	~Map() = default;
	Map(Map const&) = delete;
	Map(Map&&) = delete;
	Map& operator=(Map const&) = delete;
	Map& operator=(Map&&) = delete;

	static Map singleton;

	std::vector<MapLayer> layers;
};

#endif
