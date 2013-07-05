#ifndef MAP_HPP_
#define MAP_HPP_

#include "tileset.hpp"

#include "SDL/SDL.h"

#include <vector>

struct MapTile {
	int value;
};

class MapLayer {
public:
	MapLayer() = default;
	MapLayer(MapLayer const&) = default;
	MapLayer(MapLayer&&) = default;
	~MapLayer() = default;

	void Generate(int width, int height, int defaultValue);
	void Clear();

	void DrawTo(SDL_Surface* const, int x, int y);

	//accessors and mutators
	int SetTile(int x, int y, int value);
	int GetTile(int x, int y);

	int GetWidth() const;
	int GetHeight() const;

	Tileset* GetTileset() { return &tileset; }

private:
	std::vector<std::vector<MapTile>> tiles;
	Tileset tileset;
	//metadata?

	friend class Map;
};

class Map {
public:
	Map() = default;
	~Map() = default;

	void Generate(int layerCount, int width, int height, int defaultValue);
	void Clear();

	void DrawLayerTo(SDL_Surface* const, int layer, int x, int y);

	//TODO: save
	//TODO: load
	//TODO: insert layer
	//TODO: delete layer

	//accessors and mutators
	int SetTile(int l, int x, int y, int value);
	int GetTile(int l, int x, int y);

	MapLayer* GetLayer(int l);

	int GetLayers() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	std::vector<MapLayer> layers;
	//TODO: tilesets
	//metadata?
};

#endif
