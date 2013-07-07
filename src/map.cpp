#include "map.hpp"

#include <stdexcept>

//bah, this is a crappy shortcut, but it works
#define CheckVecRange(vec, idx) \
	if (idx < 0 || idx >= vec.size()) { throw(std::out_of_range("layer index out of range")); }


void Map::Generate(int l, int w, int h, int v) {
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

void Map::InsertLayer(int l, int dv) {
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

int Map::SetTile(int l, int x, int y, int v) {
	CheckVecRange(layers, l);
	return layers[l].SetTile(x, y, v);
}

int Map::GetTile(int l, int x, int y) {
	CheckVecRange(layers, l);
	return layers[l].GetTile(x, y);
}

MapLayer* Map::GetLayer(int l) {
	CheckVecRange(layers, l);
	return &layers[l];
}
