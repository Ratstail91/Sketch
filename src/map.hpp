#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <list>

//TODO: tilesets

struct MapTile {
	int value;
};

class MapLayer {
public:
	MapLayer() = default;
	~MapLayer() = default;

	void Generate(int width, int height, int value);
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

	void Generate(int layers, int width, int height, int value);
	void Clear();

	//TODO: save
	//TODO: load

	int SetTile(int l, int x, int y, int value);
	int GetTile(int l, int x, int y);

	int GetLayers() const;
	int GetWidth() const;
	int GetHeight() const;

private:
	std::list<MapLayer> layers;
	//TODO: tilesets
	//metadata?
};

#endif
