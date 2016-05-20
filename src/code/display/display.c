// Implementation of the display methods

// Required headers
#include "editor/utility.h"
#include "display/display.h"

void displayFrame( char *win_name ) {
	int len = _strlen( win_name );

	if( SCREEN_WIDTH < len + FRAME_WIDTH + 10 )
		return;

	int x = FRAME_WIDTH, y = 0;
	move( y, x );
	addch( '+' );
	for( x = FRAME_WIDTH + 1; x < FRAME_WIDTH + 4; x++ )
		addch( '-' );
	addch( ' ' );
	printw( win_name );
	x += len + 2;
	move( y, x );
	for( ; x < SCREEN_WIDTH - 1; x++ )
		addch( '-' );
	addch( '+' );

	for( y = 1; y < SCREEN_HEIGHT - 1; y++ ) {
		move( y, FRAME_WIDTH );
		addch( '|' );
		move( y, SCREEN_WIDTH - 1 );
		addch( '|' );
	}

	move( SCREEN_HEIGHT - 1, FRAME_WIDTH );
	addch( '+' );
	for( x = FRAME_WIDTH + 1; x < SCREEN_WIDTH - 1; x++ )
		addch( '-' );
	addch( '+' );
}

void drawText( Text *t ) {
	int LEFT = FRAME_WIDTH + 1;
	int RIGHT = SCREEN_WIDTH - 1;
	int TOP = 1;
	int BOTTOM = SCREEN_HEIGHT - 1;
	int HEIGHT = BOTTOM - TOP;
	int WIDTH = RIGHT - LEFT;

	Line *l = t->top;
	Node *n = l->head;

	int x = LEFT, y = TOP;
	while( l && y < BOTTOM ) {
		move( y, x );
		int count = 0;
		while( n != NULL && n->c != '\n' && count < WIDTH ) {
			addch( n->c );
			x++;
			count++;
			n = n->next;
		}
		y++;
		x = LEFT;

		if( !n )
			return;
		if( n->c == '\n' ) {
			l = l->next;
			if( l )
				n = l->head;
		}
	}
}

void clearDisplay( ) {
	int x = 0, y = 0;
	move( y, x );
	for( y = 0; y < SCREEN_HEIGHT; y++ )
		for( x = 0; x < SCREEN_WIDTH; x++ )
			addch( ' ' );
}

void updateDisplay( Text *t, Cursor *cursor, char *win_name ) {
	clearDisplay( );
	displayFrame( win_name );
	drawText( t );
}
