#ifndef KR_COLORS_H_
#define KR_COLORS_H_

#include "SDL.h"

enum {
	C_BLACK,
	C_WHITE,
	C_RED,
	C_GREEN,
	C_BLUE,
	C_DGREY,
	C_MGREY,
	C_LGREY,
	C_HOTPINK,
};

extern SDL_Color colors[];

#define MapRGB(format, color) SDL_MapRGB(format, color.r, color.g, color.b)

#endif
