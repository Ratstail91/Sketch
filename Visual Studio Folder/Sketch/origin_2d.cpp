/* File Name: origin_2d.cpp
 * Author: Kayne Ruse
 * Date: 27/6/2012
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
 *     Handle position and motion on a 2D plane.
*/
#include "origin_2d.h"

//-------------------------
//Public access members
//-------------------------

Origin2D::Origin2D(float x, float y) {
	m_fOriginX = x;
	m_fOriginY = y;
	m_fMotionX = 0;
	m_fMotionY = 0;
}

void Origin2D::Update(int iDelta) {
	m_fOriginX += iDelta * m_fMotionX + m_fMotionX;
	m_fOriginY += iDelta * m_fMotionY + m_fMotionY;
}

//-------------------------
//Positon in 2D
//-------------------------

void Origin2D::SetOriginPosition(float x, float y) {
	m_fOriginX = x;
	m_fOriginY = y;
}

float Origin2D::SetOriginX(float x) {
	return m_fOriginX = x;
}

float Origin2D::SetOriginY(float y) {
	return m_fOriginY = y;
}

void Origin2D::ShiftOriginPosition(float x, float y) {
	m_fOriginX += x;
	m_fOriginY += y;
}

float Origin2D::ShiftOriginX(float x) {
	return m_fOriginX += x;
}

float Origin2D::ShiftOriginY(float y) {
	return m_fOriginY += y;
}

float Origin2D::GetOriginX() {
	return m_fOriginX;
}

float Origin2D::GetOriginY() {
	return m_fOriginY;
}

//-------------------------
//Motion in 2D
//-------------------------

void Origin2D::SetMotion(float x, float y) {
	m_fMotionX = x;
	m_fMotionY = y;
}

float Origin2D::SetMotionX(float x) {
	return m_fMotionX = x;
}

float Origin2D::SetMotionY(float y) {
	return m_fMotionY = y;
}

void Origin2D::ShiftMotion(float x, float y) {
	m_fMotionX += x;
	m_fMotionY += y;
}

float Origin2D::ShiftMotionX(float x) {
	return m_fMotionX += x;
}

float Origin2D::ShiftMotionY(float y) {
	return m_fMotionY += y;
}

float Origin2D::GetMotionX() {
	return m_fMotionX;
}

float Origin2D::GetMotionY() {
	return m_fMotionY;
}

void Origin2D::StopMotion() {
	m_fMotionX = 0;
	m_fMotionY = 0;
}
