#include<iostream>
#include "snake.hpp"
using namespace std;
int main()
{
	//console curser object created used in win api to move cursor
	CONSOLE_CURSOR_INFO ci;
	//curser size
	ci.dwSize=50;
	//setting curser as invisible
	ci.bVisible=0;
	//passing arguments to function in windows.h
	SetConsoleCursorInfo(hOut,&ci);
//function which matches the system time and generates different random values
srand (time(NULL));
//snake class object
Snake *s = new Snake(20,35);
s->driver();
return 0;
}