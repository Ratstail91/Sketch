#ifndef KR_TILESET_H_
#define KR_TILESET_H_

#include <string>
#include "SDL.h"

//This is a basic file loading class

class Tileset {
public:
	Tileset(std::string fname, Uint32 w, Uint32 h);
	~Tileset();

	std::string GetFileName();
	SDL_Surface* GetSurface();

	Uint32 GetXCount();
	Uint32 GetYCount();
	Uint32 GetWidth();
	Uint32 GetHeight();

	Uint32 GetCount();
	Uint32 GetStart();
	Uint32 SetStart(Uint32 iStartIndex);

private:
	std::string m_sFileName;
	SDL_Surface* m_pSurface;

	Uint32 m_iXCount;
	Uint32 m_iYCount;
	Uint32 m_iWidth;
	Uint32 m_iHeight;

	Uint32 m_iCount;
	Uint32 m_iStart;
};

#endif
