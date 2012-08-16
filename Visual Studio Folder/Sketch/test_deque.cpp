#include <iostream>
#include <deque>
#include <string>
using namespace std;


static deque<string> terminal;


int main() {
	terminal.push_back("hello world");
	terminal.push_back("foo");
	terminal.push_back("bar");

	for (deque<string>::iterator it = terminal.begin(); it != terminal.end(); it++) {
		cout << *it << endl;
	}

	return 0;
}