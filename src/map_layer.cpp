#include "map_layer.hpp"

#include <stdexcept>

#define CheckRange(x, y) \
	if (x < 0 || y < 0 || x >= tiles.size() || y >= tiles.begin()->size()) \
		throw(std::out_of_range("tile index out of range"));


void MapLayer::Generate(int width, int height, int defaultValue) {
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

int MapLayer::SetTile(int x, int y, int value) {
	CheckRange(x, y);
	return tiles[x][y].value = value;
}

int MapLayer::GetTile(int x, int y) {
	CheckRange(x, y);
	return tiles[x][y].value;
}
