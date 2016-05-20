// Project-defined headers
#include <stdlib.h>

#include "editor/structs.h"
#include "editor/global_variables.h"
#include "editor/ncurses_interface.h"
#include "editor/chars.h"
#include "display/display.h"

int	SCREEN_WIDTH;
int	SCREEN_HEIGHT;
int	FRAME_WIDTH;

// Starting point of program
int main( int argc, char *argv[] ) {
	// Variables
	int exit_flag, edit_flag, exit_status;
	int ch;
	Text *t = createText( );
	Cursor *cursor = ( Cursor* ) malloc( sizeof( Cursor ) );
	cursor->linum = 1;
	cursor->node_num = 0;

	// Start ncurses screen with required options
	initNcurses( );
	getDimensions( );
	FRAME_WIDTH = 3;

	// Initialize exit and edit flags to 0
	exit_flag = 0;
	edit_flag = 0;

	// Draw empty frame
	updateDisplay( t, cursor, "window" );

	// Start infinite loop which accepts character then processes what to do with it
	while( 1 ) {
		// Reset the edit flag
		edit_flag = 1;
		
		// Get the key typed
		ch = getch( );

		// Switch for the different cases
		switch( ch ) {
			// Movement/Arrow keys
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;
			case KEY_LEFT:
				break;
			case KEY_RIGHT:
				break;

			// TAB key
			case 9:
				break;

			// Newline (Return key)
			case 10:
				break;

			// Backspace key
			case 127:
				break;

			// Escape key
			case 27:
				exit_flag = 1;
				break;

			// Default (any other key)
			default:
				addChar( t, cursor, ch );
				edit_flag = 1;
				break;
		}
		// Check if we need to exit
		if( exit_flag == 1 ) {
			exit_status = 0;
			break;
		}

		// Check if the text itself has been edited
		if( edit_flag == 1 ) {
			getDimensions( );
			updateDisplay( t, cursor, "window" );
		}
	}

	endNcurses( );
	return exit_status;
}
