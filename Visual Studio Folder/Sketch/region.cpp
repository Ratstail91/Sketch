#include "region.h"

Region::Region(Uint32 x, Uint32 y, Uint32 l):
m_iXCount(x), m_iYCount(y), m_iLCount(l)
{
	GenArray();
}

Region::~Region() {
	ClrArray();
}

Uint32 Region::GetTile(Uint32 x, Uint32 y, Uint32 l) {
	return m_pArray[x][y][l];
}

Uint32 Region::SetTile(Uint32 x, Uint32 y, Uint32 l, Uint32 v) {
	return m_pArray[x][y][l] = v;
}

void Region::GenArray() {
	//generate and zero the array
	m_pArray = new Uint32**[m_iXCount];
	for (Uint32 i = 0; i < m_iXCount; i++) {
		m_pArray[i] = new Uint32*[m_iYCount];
		for (Uint32 j = 0; j < m_iYCount; j++) {
			m_pArray[i][j] = new Uint32[m_iLCount];
			for (Uint32 k = 0; k < m_iLCount; k++) {
				m_pArray[i][j][k] = 0;
			}
		}
	}
}

void Region::ClrArray() {
	//delete each nested array
	for (Uint32 i = 0; i < m_iXCount; i++) {
		for (Uint32 j = 0; j < m_iYCount; j++) {
			delete[] m_pArray[i][j];
		}
		delete[] m_pArray[i];
	}
	delete[] m_pArray;
}
