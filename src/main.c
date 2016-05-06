#include <ncurses.h>

#include "editor/structs.h"
#include "editor/chars.h"
#include "editor/cursor.h"
#include "editor/display.h"
#include "editor/utility.h"


int	SCREEN_HEIGHT = 25;
int	SCREEN_WIDTH = 80;

int main() {
	int ch, exit_flag, edit_flag;
	Text *t = createText( );
	Cursor cursor;
	cursor.x = 0;
	cursor.y = 0;

	initscr( );
	raw( );
	noecho( );
	keypad( stdscr, TRUE );

	getmaxyx( stdscr, SCREEN_HEIGHT, SCREEN_WIDTH );

	exit_flag = 0;

	while( 1 ) {
		ch = getch( );
		switch( ch ) {
			case 27:			/* Escape key */
				exit_flag = 1;
				break;
			case 127:			/* Backspace key */
				addBackspace( t, &cursor );
				edit_flag = 1;
				break;
			case 10:			/* Enter key */
				addNewline( t, &cursor );
				edit_flag = 1;
				break;
			case 9:				/* TAB key */
				addTab( t, &cursor );
				edit_flag = 1;
				break;
			case KEY_UP:
				moveUp( t, &cursor );
				break;
			case KEY_DOWN:
				moveDown( t, &cursor );
				break;
			case KEY_LEFT:
				moveLeft( t, &cursor );
				break;
			case KEY_RIGHT:
				moveRight( t, &cursor );
				break;
			default:
				addChar( t, &cursor, ch );
				edit_flag = 1;
				break;
		}
		if( exit_flag == 1 )
			break;
		if( edit_flag == 1 ) {
			clearDisplay( );
			updateDisplay( t, &cursor );
			refresh( );
		}
	}

	endwin( );

	clearText( t );

	return 0;
}
