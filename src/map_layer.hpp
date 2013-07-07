#ifndef MAPLAYER_HPP_
#define MAPLAYER_HPP_

#include "map_tile.hpp"
#include "tileset.hpp"

#include "SDL/SDL.h"

#include <vector>

class MapLayer {
public:
	MapLayer() = default;
	MapLayer(int w, int h, int v) { Generate(w, h, v); }

	void Generate(int width, int height, int defaultValue);
	void Clear();

	void DrawTo(SDL_Surface* const, Tileset*, int x, int y);

	//accessors and mutators
	int SetTile(int x, int y, int value);
	int GetTile(int x, int y);

	int GetWidth() const;
	int GetHeight() const;

private:
	std::vector<std::vector<MapTile>> tiles;
};

#endif
