#include "map.hpp"

#include <stdexcept>

//-------------------------
//MapLayer definitions
//-------------------------

void MapLayer::Generate(int width, int height, int value) {
	using std::vector;
	tiles.clear();
	/* 1. create a vector<vector<MapTile>> structure of size "width"
	 * 2. create a vector<MapTile> structure of size "height", which is the default value for above
	 * 3. create a MapTile structure with the value "value", which is the default value for above
	 * 4. cast is as an rvalue to prevent expensive movement
	*/
	tiles = move(vector<vector<MapTile>>(width, vector<MapTile>(height, MapTile{value})));
}

void MapLayer::Clear() {
	tiles.clear();
}

int MapLayer::SetTile(int x, int y, int value) {
	if (x >= tiles.size()) {
		throw(std::runtime_error("tile index out of range"));
	}
	if (y >= tiles.begin()->size()) {
		throw(std::runtime_error("tile index out of range"));
	}
	return tiles[x][y].value = value;
}

int MapLayer::GetTile(int x, int y) {
	if (x >= tiles.size()) {
		throw(std::runtime_error("tile index out of range"));
	}
	if (y >= tiles.begin()->size()) {
		throw(std::runtime_error("tile index out of range"));
	}
	return tiles[x][y].value;
}

int MapLayer::GetWidth() const {
	return tiles.size();
}

int MapLayer::GetHeight() const {
	if (tiles.size() == 0) {
		return 0;
	}
	return tiles.begin()->size();
}

//-------------------------
//Map definitions
//-------------------------

void Map::Generate(int layers, int width, int height, int value) {
	//
}

void Map::Clear() {
	//
}

int Map::SetTile(int l, int x, int y, int value) {
	//
}

int Map::GetTile(int l, int x, int y) {
	//
}

int Map::GetLayers() const {
	//
}

int Map::GetWidth() const {
	//
}

int Map::GetHeight() const {
	//
}
