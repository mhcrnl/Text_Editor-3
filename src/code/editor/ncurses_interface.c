// Implementation of ncurses interface functions

#include "editor/ncurses_interface.h"

void initNcurses( ) {
	initscr( );
	raw( );
	noecho( );
	keypad( stdscr, TRUE );
}

void getDimensions( ) {
	getmaxyx( stdscr, SCREEN_HEIGHT, SCREEN_WIDTH );
}

void endNcurses( ) {
	endwin( );
}
