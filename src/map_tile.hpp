#ifndef MAPTILE_HPP_
#define MAPTILE_HPP_

/* TODO: allow this to be modified (at runtime?), to allow *massive* maps
 * Could use a macro TILE_INVISIBLE defined as the maximum value for "value"'s type,
 * and thread it into the existing code. That way, this could be an unsigned char,
 * or even have a non-standard size (bit fields).
*/

struct MapTile {
	int value;
	//other metadata
};

#endif
