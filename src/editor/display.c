/* #################################################################### */
/*			REQUIRED HEADERS				*/
/* #################################################################### */

#include <ncurses.h>

#include "editor/display.h"
#include "global_variables.h"

/* #################################################################### */
/*			IMPLEMENTATION FUNCTIONS			*/
/* #################################################################### */


/* #################################################################### */
/*			INTERFACE FUNCTIONS				*/
/* #################################################################### */

void clearDisplay( ) {
	int x = 0, y = 0;
	move( y, x );

	for( y = 0; y < SCREEN_HEIGHT; y++ ) {
		for( x = 0; x < SCREEN_WIDTH; x++ ) {
			addch( ' ' );
		}
	}

	move( 0, 0 );
}

void updateDisplay( Text *t, Cursor *cursor ) {
	Line *l = t->top;
	Node *n = l->head;

	int x = 0, y = 0;
	while( y < SCREEN_HEIGHT ) {
		while( n ) {
			addch( n->c );
			if( n->c == '\n' )
				break;
			n = n->next;
			if( ++x == SCREEN_WIDTH ) {
				x = 0;
				if( ++y == SCREEN_HEIGHT ) {
					break;
				}
			}
		}
		x = 0;
		y++;
		l = l->next;
		if( l == NULL )
			break;
	}
	move( cursor->y, cursor->x );
}
