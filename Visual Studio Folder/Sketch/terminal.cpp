#include <stdexcept>
#include "terminal.h"
using namespace std;

void Terminal::KeyDown(SDL_keysym const& keysym) {
	//shift modifier
	if (keysym.mod & KMOD_SHIFT) {
		switch(keysym.sym) {
			//numbers
			case SDLK_1: m_sInput += '!'; break;
			case SDLK_2: m_sInput += '@'; break;
			case SDLK_3: m_sInput += '#'; break;
			case SDLK_4: m_sInput += '$'; break;
			case SDLK_5: m_sInput += '%'; break;
			case SDLK_6: m_sInput += '^'; break;
			case SDLK_7: m_sInput += '&'; break;
			case SDLK_8: m_sInput += '*'; break;
			case SDLK_9: m_sInput += '('; break;
			case SDLK_0: m_sInput += ')'; break;

			//punctuation
			case SDLK_BACKQUOTE:	m_sInput += '~'; break;
			case SDLK_MINUS:		m_sInput += '_'; break;
			case SDLK_EQUALS:		m_sInput += '+'; break;
			case SDLK_LEFTBRACKET:	m_sInput += '{'; break;
			case SDLK_RIGHTBRACKET:	m_sInput += '}'; break;
			case SDLK_BACKSLASH:	m_sInput += '|'; break;
			case SDLK_SEMICOLON:	m_sInput += ':'; break;
			case SDLK_QUOTE:		m_sInput += '"'; break;
			case SDLK_COMMA:		m_sInput += '<'; break;
			case SDLK_PERIOD:		m_sInput += '>'; break;
			case SDLK_SLASH:		m_sInput += '?'; break;

			//error case
			case SDLK_ESCAPE: break;
			case SDLK_RETURN: break;
			case SDLK_DELETE: break;

			default:
				if (isalpha(keysym.sym)) {
					m_sInput += keysym.sym + ('A' - 'a');
				}

				if (isspace(keysym.sym)) {
					m_sInput += keysym.sym;
				}
		}
		return;
	}

	//no recognised modifiers
	switch(keysym.sym) {
		//punctuation
		case SDLK_BACKQUOTE:	m_sInput += '`'; break;
		case SDLK_MINUS:		m_sInput += '-'; break;
		case SDLK_EQUALS:		m_sInput += '='; break;
		case SDLK_TAB:			m_sInput += "    "; break; //might need tweak
		case SDLK_LEFTBRACKET:	m_sInput += '['; break;
		case SDLK_RIGHTBRACKET:	m_sInput += ']'; break;
		case SDLK_BACKSLASH:	m_sInput += '\\'; break;
		case SDLK_SEMICOLON:	m_sInput += ';'; break;
		case SDLK_QUOTE:		m_sInput += '\''; break;
		case SDLK_COMMA:		m_sInput += ','; break;
		case SDLK_PERIOD:		m_sInput += '.'; break;
		case SDLK_SLASH:		m_sInput += '/'; break;

		//error case
		case SDLK_ESCAPE: break;
		case SDLK_RETURN: Push(); break;
		case SDLK_DELETE: m_sInput.clear(); break;

		//delete the last character
		case SDLK_BACKSPACE:
			if (m_sInput.size() > 0) {
				m_sInput.erase( m_sInput.end()-1 );
			}
			break;

		default:
			if (isalnum(keysym.sym) || isspace(keysym.sym)) {
				m_sInput += keysym.sym;
				break;
			}
			break;
	};
}

void Terminal::KeyUp(SDL_keysym const& keysym) {
	//blank
}

void Terminal::Push(std::string s) {
	if (s.size() == 0 && m_sInput.size() != 0) {
		m_lines.push_back(m_sInput);
		m_sInput.clear();
	}
	else if (s.size() != 0) {
		m_lines.push_back(s);
	}
}

string Terminal::GetLine(int index) {
	//+ive index counts from the front (oldest),
	//-ive index counts from the back (newest),
	//0 indexed, otherwise mimics lua stack

	if (index < 0) {
		return m_lines.at(m_lines.size() + index);
	}
	else {
		return m_lines.at(index);
	}
}
