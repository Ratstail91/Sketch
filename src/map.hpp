#ifndef MAP_HPP_
#define MAP_HPP_

#include "map_layer.hpp"
#include "tileset.hpp"

#include "SDL/SDL.h"

#include <vector>

class Map {
public:
	Map() = default;
	Map(int l, int w, int h, int v) { Generate(l, w, h, v); }

	void Generate(int layerCount, int width, int height, int defaultValue = -1);
	void Clear();

	void DrawLayerTo(SDL_Surface* const, Tileset*, int layer, int x, int y);

	//accessors and mutators
	void InsertLayer(int layer, int defaultValue = -1);
	void DeleteLayer(int layer);

	int SetTile(int l, int x, int y, int value);
	int GetTile(int l, int x, int y);

	MapLayer* GetLayer(int l);

	int GetLayerCount() const { return layers.size(); }
	int GetWidth() const { return layers.size() ? layers.begin()->GetWidth() : 0; }
	int GetHeight() const { return layers.size() ? layers.begin()->GetHeight() : 0; }

private:
	std::vector<MapLayer> layers;
	//metadata?
};

#endif
