#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>

//TODO: tilesets

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

	int SetTile(int x, int y, int value);
	int GetTile(int x, int y);

	int GetWidth() const;
	int GetHeight() const;

private:
	std::vector<std::vector<MapTile>> tiles;
	//metadata?

	friend class Map;
};

class Map {
public:
	Map() = default;
	~Map() = default;

	void Generate(int layerCount, int width, int height, int defaultValue);
	void Clear();

	//TODO: save
	//TODO: load
	//TODO: insert layer
	//TODO: delete layer

	int SetTile(int l, int x, int y, int value);
	int GetTile(int l, int x, int y);

	int GetLayers() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	std::vector<MapLayer> layers;
	//TODO: tilesets
	//metadata?
};

#endif
