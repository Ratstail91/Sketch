/* File Name: region.cpp
 * Author: Kayne Ruse
 * Date: 28/8/2012
 * Copyright: (c) Kayne Ruse 2012
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * Description:
 *     ...
*/
#include <stdexcept>
#include "region.h"

#define CHECK_RANGE \
	if (x >= m_iXCount || y >= m_iYCount || l >= m_iLCount) \
		throw(std::out_of_range("Parameter out of range of region"));

Region::Region() {
	m_iXCount = 0;
	m_iYCount = 0;
	m_iLCount = 0;
	m_pArray = NULL;
}

Region::~Region() {
	Unload();
}

void Region::Load(Uint32 x, Uint32 y, Uint32 l) {
	Unload();
	m_iXCount = x;
	m_iYCount = y;
	m_iLCount = l;
	GenArray();
}

void Region::Unload() {
	ClrArray();
	m_iXCount = 0;
	m_iYCount = 0;
	m_iLCount = 0;
	m_pArray = NULL;
}

bool Region::IsLoaded() {
	if (!m_pArray)
		return false;
	return true;
}

Uint32 Region::GetTile(Uint32 x, Uint32 y, Uint32 l) {
	CHECK_RANGE;
	return m_pArray[x][y][l];
}

Uint32 Region::SetTile(Uint32 x, Uint32 y, Uint32 l, Uint32 v) {
	CHECK_RANGE;
	return m_pArray[x][y][l] = v;
}

Uint32 Region::GetXCount() {
	return m_iXCount;
}

Uint32 Region::GetYCount() {
	return m_iYCount;
}

Uint32 Region::GetLCount() {
	return m_iLCount;
}

void Region::GenArray() {
	if (m_pArray != NULL) {
		throw(std::logic_error("Region array is not null"));
	}

	if (!m_iXCount || !m_iYCount || !m_iLCount) return;

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
	if (m_pArray == NULL) return;

	if (!m_iXCount || !m_iYCount || !m_iLCount) return;

	//delete each nested array
	for (Uint32 i = 0; i < m_iXCount; i++) {
		for (Uint32 j = 0; j < m_iYCount; j++) {
			delete[] m_pArray[i][j];
		}
		delete[] m_pArray[i];
	}
	delete[] m_pArray;
}
