#include <ncurses.h>
#include <stdlib.h>

#define MAX_WIDTH  80
#define MAX_HEIGHT 24

/* #################################################################### */
/* Structs								*/
/* #################################################################### */

typedef struct line_s {
	char content[MAX_WIDTH + 1];
	struct line_s *next;
	struct line_s *prev;
} Line;

typedef struct text_s {
	Line *first_line;			/* First line in the text */
	Line *display_top_line;			/* Topmost line which fits in the display */
	Line *current_line;			/* Current line which the cursor is at */
	Line *display_bottom_line;		/* Bottom line which fits in the display */
	Line *last_line;			/* Last line of the text */
	int num_lines;				/* The number of lines in the text */
	int num_display_lines;			/* Number of lines currently being displayed */
	int cursor_index_in_line;		/* The index at which the cursor is in the current line */
} Text;

typedef struct cursor_s {			/* For easier handling of the cursor */
	int y;
	int x;
} Cursor;

/* #################################################################### */
/* Utility Functions							*/
/* #################################################################### */

int _strlen( char *str ) {
	int len = 0;
	while( str[len] )
		len++;
	return len;
}

/* #################################################################### */
/* Editor Functions							*/
/* #################################################################### */

Line *createEmptyLine( ) {
	Line *line = ( Line* ) malloc( sizeof( Line ) );
	line->next = NULL;
	line->prev = NULL;
	line->content[0] = '\0';
	return line;
}

Text *createEmptyText( ) {
	Text *text = ( Text* ) malloc( sizeof( Text ) );
	text->first_line = createEmptyLine( );
	text->display_top_line = text->current_line = text->display_bottom_line = text->last_line = text->first_line;
	text->num_lines = text->num_display_lines = 1;
	text->cursor_index_in_line = 0;
}

void charAdded( Text *text, char c ) {
	text->current_line->content[text->cursor_index_in_line] = c;
	text->current_line->content[text->cursor_index_in_line + 1] = '\0';
	if( ++text->cursor_index_in_line == MAX_WIDTH ) {
		text->current_line->content[text->cursor_index_in_line] = '\n';
		text->current_line->content[text->cursor_index_in_line + 1] = '\0';
		text->cursor_index_in_line = 0;
		Line *temp_line = createEmptyLine( );
		temp_line->prev = text->current_line;
		text->current_line->next = temp_line;
		if( text->current_line == text->last_line )
			text->last_line = temp_line;
		if( text->current_line == text->display_bottom_line )
			text->display_bottom_line = text->display_bottom_line->next;
		text->num_display_lines++;
		if( text->num_display_lines > MAX_HEIGHT )
			text->display_top_line = text->display_top_line->next;
		text->current_line = temp_line;
	}
}

void newlineAdded( Text *text ) {
	text->current_line->content[text->cursor_index_in_line] = '\n';
	text->current_line->content[text->cursor_index_in_line + 1] = '\0';
	text->cursor_index_in_line = 0;
	Line *temp_line = createEmptyLine( );
	temp_line->prev = text->current_line;
	text->current_line->next = temp_line;
	if( text->current_line == text->last_line )
		text->last_line = temp_line;
	if( text->current_line == text->display_bottom_line )
		text->display_bottom_line = text->display_bottom_line->next;
	text->num_display_lines++;
	if( text->num_display_lines > MAX_HEIGHT )
		text->display_top_line = text->display_top_line->next;
	text->current_line = temp_line;
}

void backspaceAdded( Text *text ) {
	if( text->cursor_index_in_line == 0 ) {
		/* TO BE DONE: Add support for backspace to previous line */
	}
	else {
		
	}
}

void moveUp( Text *text ) {
	Cursor cursor;
	int len;
	getyx( stdscr, cursor.y, cursor.x );
	move( cursor.y - 1, cursor.x );
	if( text->current_line == text->first_line )
		return;
	else if ( text->current_line == text->display_top_line ) {
		text->display_top_line = text->display_top_line->prev;
		text->num_display_lines++;
		if( text->num_display_lines > MAX_HEIGHT ) {
			text->display_bottom_line = text->display_bottom_line->prev;
		}
		text->current_line = text->current_line->prev;
		len = _strlen( text->current_line->content );
		if( len < text->cursor_index_in_line )
			text->cursor_index_in_line = len;
	}
	else
		text->current_line = text->current_line->prev;
		len = _strlen( text->current_line->content );
		if( len < text->cursor_index_in_line )
			text->cursor_index_in_line = len;
}

void moveDown( Text *text ) {
	Cursor cursor;
	int len;
	getyx( stdscr, cursor.y, cursor.x );
	move( cursor.y - 1, cursor.x );
	if( text->current_line == text->last_line )
		return;
	else if ( text->current_line == text->display_bottom_line ) {
		text->display_bottom_line = text->display_bottom_line->next;
		text->num_display_lines++;
		if( text->num_display_lines > MAX_HEIGHT ) {
			text->display_top_line = text->display_top_line->next;
		}
		text->current_line = text->current_line->next;
		len = _strlen( text->current_line->content );
		if( len < text->cursor_index_in_line )
			text->cursor_index_in_line = len;
	}
	else
		text->current_line = text->current_line->next;
		len = _strlen( text->current_line->content );
		if( len < text->cursor_index_in_line )
			text->cursor_index_in_line = len;
}

void moveLeft( Text *text ) {

}

void moveRight( Text *text ) {

}

/* #################################################################### */
/* Display Functions							*/
/* #################################################################### */

void clearDisplay( ) {
	int row = 0, col = 0;
	for( ; row < MAX_HEIGHT; row++ ) {
		for( ; col < MAX_WIDTH; col++ ) {
			addch( ' ' );
		}
	}
}

void updateDisplay( Text *text ) {
	Line *line = text->display_top_line;
	move( 0, 0 );
	while( line != text->display_bottom_line ) {
		printw( "%s", line->content );
		line = line->next;
	}
	printw( "%s", line->content );
}

/* #################################################################### */
/* Main									*/
/* #################################################################### */

int main( ) {
	int input_char, exit_flag, change_flag;
	Text *text = createEmptyText();
	Cursor cursor;

	initscr();
	raw();
	noecho();
	keypad( stdscr, TRUE );

	exit_flag = 0;

	while( 1 ) {
		change_flag = 0;

		input_char = getch( );
		switch( input_char ) {
			case KEY_UP:
				moveUp( text );
				break;
			case KEY_DOWN:
				moveDown( text );
				break;
			case KEY_LEFT:
				moveLeft( text );
				break;
			case KEY_RIGHT:
				moveRight( text );
				break;
			case 27:
				exit_flag = 1;
				break;
			case 10:
				newlineAdded( text );
				change_flag = 1;
				break;
			case 127:
				backspaceAdded( text );
				change_flag = 1;
			default :
				charAdded( text, input_char );
				change_flag = 1;
		}

		if( exit_flag )
			break;

		if( change_flag ) {
			clearDisplay( );
			updateDisplay( text );
			refresh();
		}
	}

	endwin();
	return 0;
}
