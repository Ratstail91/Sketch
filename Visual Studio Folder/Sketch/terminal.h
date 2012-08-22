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
