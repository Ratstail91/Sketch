#ifndef MAP_HPP_
#define MAP_HPP_

#include "map_layer.hpp"
#include "tileset.hpp"

#include "SDL/SDL.h"

#include <vector>

class Map {
public:
	void Generate(int layerCount, int width, int height, int defaultValue);
	void Clear();

	void DrawLayerTo(SDL_Surface* const, Tileset*, int layer, int x, int y);

	//TODO: save
	//TODO: load
	//TODO: insert layer
	//TODO: delete layer
	//TODO: handle tilesets

	//accessors and mutators
	int SetTile(int l, int x, int y, int value);
	int GetTile(int l, int x, int y);

	MapLayer* GetLayer(int l);

	int GetLayerCount() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	std::vector<MapLayer> layers;
	//metadata?
};

#endif
