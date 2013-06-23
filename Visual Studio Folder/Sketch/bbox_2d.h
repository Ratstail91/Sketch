/* File Name: bbox_2d.h
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
 *     Detect and handle box collisions on a 2D plane.
*/
#ifndef KR_BBOX2D_H_
#define KR_BBOX2D_H_ 2012062701

class BBox2D {
public:
	/* Box struct */
	typedef struct Rect {
		float x;
		float y;
		float w;
		float h;
	}Rect;

	enum {FALSE=0, EDGE=1, INSIDE=2, OUTSIDE=3};

	/* Public access members */
	BBox2D(float x=0, float y=0, float w=0, float h=0);
	BBox2D(Rect box);

	virtual Rect GetWorldBBox	();
	virtual int CheckWorldBBox	(Rect box);
	virtual Rect GetWorldBBox	(float x, float y);
	virtual int CheckWorldBBox	(float x, float y, Rect box);

	/* Accessors and mutators */
	Rect SetBBox(float x, float y, float w, float h);
	Rect SetBBox(Rect box);

	Rect GetBBox();

	float SetBBoxX(float);
	float SetBBoxY(float);
	float SetBBoxW(float);
	float SetBBoxH(float);

	float GetBBoxX();
	float GetBBoxY();
	float GetBBoxW();
	float GetBBoxH();

private:
	/* Private access members */
	Rect m_rect;
};

#endif
