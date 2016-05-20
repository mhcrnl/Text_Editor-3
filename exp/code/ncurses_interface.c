#include "ncurses_interface.h"

void initNcurses( ) {
	initscr( );
	raw( );
	noecho( );
	keypad( stdscr, TRUE );
}

void endNcurses( ) {
	endwin( );
}
