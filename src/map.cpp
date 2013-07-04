#include "map.hpp"

#include <stdexcept>

//-------------------------
//MapLayer definitions
//-------------------------

void MapLayer::Generate(int width, int height, int defaultValue) {
	using std::vector;

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
	tiles = std::move(vector<vector<MapTile>>(width, vector<MapTile>(height, MapTile{defaultValue})));
}

void MapLayer::Clear() {
	tiles.clear();
}

int MapLayer::SetTile(int x, int y, int value) {
	if (x >= tiles.size() || y >= tiles.begin()->size()) {
		throw(std::out_of_range("tile index out of range"));
	}
	return tiles[x][y].value = value;
}

int MapLayer::GetTile(int x, int y) {
	if (x >= tiles.size() || y >= tiles.begin()->size()) {
		throw(std::out_of_range("tile index out of range"));
	}
	return tiles[x][y].value;
}

int MapLayer::GetWidth() const {
	return tiles.size();
}

int MapLayer::GetHeight() const {
	if (tiles.size() <= 0) {
		return 0;
	}
	return tiles.begin()->size();
}

//-------------------------
//Map definitions
//-------------------------

void Map::Generate(int layerCount, int width, int height, int defaultValue) {
	if (layerCount <= 0) {
		throw(std::invalid_argument("Cannot generate less than one layer of tiles"));
	}

	layers.clear();
	layers.reserve(layerCount);
	MapLayer tmp;
	tmp.Generate(width, height, defaultValue);
	for (int i = 0; i < layerCount; i++) {
		//implicitly calls the copy constructor
		layers.push_back(tmp);
	}
}

void Map::Clear() {
	layers.clear();
}

int Map::SetTile(int l, int x, int y, int value) {
	if (l >= layers.size()) {
		throw(std::out_of_range("layer index out of range"));
	}
	return layers[l].SetTile(x, y, value);
}

int Map::GetTile(int l, int x, int y) {
	if (l >= layers.size()) {
		throw(std::out_of_range("layer index out of range"));
	}
	return layers[l].GetTile(x, y);
}

int Map::GetLayers() const {
	return layers.size();
}

int Map::GetWidth() const {
	if (layers.size() == 0) {
		return 0;
	}
	return layers.begin()->GetWidth();
}

int Map::GetHeight() const {
	if (layers.size() == 0) {
		return 0;
	}
	return layers.begin()->GetHeight();
}
