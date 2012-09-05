/* File Name: terminal.h
 * Author: Kayne Ruse
 * Date: 22/8/2012
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
#ifndef KR_TERMINAL_H_
#define KR_TERMINAL_H_

#include <deque>
#include <string>
#include "SDL_keyboard.h"

class Terminal {
public:
	void KeyDown	(SDL_keysym const&);
	void KeyUp		(SDL_keysym const&);

	void Push(std::string s = "");
	std::string GetLine(int);

	//oo breakers (try to avoid these)
	std::deque<std::string>* GetLines() { return &m_lines; };
	std::string* GetInput() { return &m_sInput; };
private:
	std::deque<std::string> m_lines;
	std::string m_sInput;
};

#endif
