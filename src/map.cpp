#include "map.hpp"

#include <stdexcept>

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

void Map::DrawLayerTo(SDL_Surface* const dest, Tileset* tset, int l, int x, int y) {
	if (l >= layers.size()) {
		throw(std::out_of_range("layer index out of range"));
	}
	layers[l].DrawTo(dest, tset, x, y);
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

MapLayer* Map::GetLayer(int l) {
	if (l >= layers.size()) {
		throw(std::out_of_range("layer index out of range"));
	}
	return &layers[l];
}

int Map::GetLayerCount() const {
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
