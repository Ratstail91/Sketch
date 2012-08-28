#ifndef KR_REGION_H_
#define KR_REGION_H_

#include "SDL.h"

class Region {
public:
	Region();
	~Region();

	void Load		(Uint32 x, Uint32 y, Uint32 l);
	void Unload		();
	bool IsLoaded	();

	Uint32 GetTile(Uint32 x, Uint32 y, Uint32 l);
	Uint32 SetTile(Uint32 x, Uint32 y, Uint32 l, Uint32 v);

	Uint32 GetXCount();
	Uint32 GetYCount();
	Uint32 GetLCount();

private:
	void GenArray();
	void ClrArray();

	Uint32 m_iXCount;
	Uint32 m_iYCount;
	Uint32 m_iLCount;

	Uint32*** m_pArray;
};

#endif
