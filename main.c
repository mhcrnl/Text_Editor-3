#include <ncurses.h>
#include <stdlib.h>

#define MAX_WIDTH 80
#define MAX_HEIGHT 24

/* #################################################################################### */
/* Structs                                                                              */
/* #################################################################################### */

typedef struct line_s {
        char content[MAX_WIDTH + 1];
        int length;
        int is_overflowing;
        struct line_s *next;
        struct line_s *prev;
} Line;

typedef struct text_s {
        Line *first_line;
        Line *display_top_line;
        Line *current_line;
        Line *display_bottom_line;
        Line *last_line;
        int cursor_x;
        int num_display_lines;
} Text;

typedef struct {
        int x;
        int y;
} Cursor;

/* #################################################################################### */
/* Utility Functions                                                                    */
/* #################################################################################### */

int _strlen( char *str ) {
        int len = 0;
        for( ; str[len]; len++ );
        return len;
}

void cleanUp( Text *text ) {
        Line *temp1, *temp2;
        temp1 = text->first_line;
        temp2 = text->first_line;
        while( temp1 ) {
                temp1 = temp1->next;
                free( temp2 );
                temp2 = temp1;
        }
}

/* #################################################################################### */
/* Editor Functions                                                                     */
/* #################################################################################### */

Line *createEmptyLine( ) {
        Line *line = ( Line* ) malloc( sizeof( Line ) );
        line->content[0] = '\0';
        line->length = 0;
        line->is_overflowing = 0;
        line->next = NULL;
        line->prev = NULL;
        return line;
}

Text *createEmptyText( ) {
        Text *text = ( Text* ) malloc( sizeof( Text ) );
        text->first_line = createEmptyLine( );
        text->display_top_line = text->current_line = text->display_bottom_line = text->last_line = text->first_line;
        text->cursor_x = 0;
        text->num_display_lines = 0;
}

void addChar( Text *text, Cursor *cursor, char c ) {
        if( text->current_line->is_overflowing ) {
                
        }
        else if ( text->current_line->length == MAX_WIDTH ) {
                
        }
        else {
                if( text->cursor_x == text->current_line->length ) {
                        text->current_line->content[text->cursor_x] = c;
                        text->current_line->length++;
                        text->current_line->content[text->current_line->length] = '\0';
                        text->cursor_x++;
                        
                        cursor->x++;
                }
                else {
                        int temp_index = text->current_line->length;
                        while( temp_index > text->cursor_x ) {
                                text->current_line->content[temp_index] = text->current_line->content[temp_index - 1];
                                temp_index--;
                        }
                        text->current_line->content[text->cursor_x] = c;
                        text->current_line->length++;
                        text->current_line->content[text->current_line->length] = '\0';
                        text->cursor_x++;
                        
                        cursor->x++;
                }
        }
}

void addNewline( Text *text, Cursor *cursor ) {
        
        if( text->current_line->is_overflowing ) {
                
        }
        else if ( text->current_line->length == MAX_WIDTH ) {
                
        }
        else {
                if( text->cursor_x == text->current_line->length ) {
                        text->current_line->content[text->cursor_x] = '\n';
                        text->current_line->length;
                        text->current_line->content[text->current_line->length + 1] = '\0';
                        
                        Line *temp_line = createEmptyLine( );
                        temp_line->prev = text->current_line;
                        temp_line->next = text->current_line->next;
                        text->current_line->next = temp_line;
                        if( temp_line->next )
                                temp_line->next->prev = temp_line;
                        
                        if( text->last_line == text->current_line ) {
                                text->last_line = temp_line;
                                text->display_bottom_line = temp_line;
                        }

                        text->num_display_lines++;

                        if( text->num_display_lines > MAX_HEIGHT ) {
                                text->display_bottom_line = text->display_bottom_line->prev;
                                text->num_display_lines--;
                        }
                        
                        text->current_line = temp_line;
        
                        text->cursor_x = 0;
                        
                        cursor->x = 0;
                        cursor->y++;
                        if( cursor->y == MAX_HEIGHT )
                                cursor->y--;
                }
                else {
                        Line *temp_line = createEmptyLine( );
                        temp_line->prev = text->current_line;
                        temp_line->next = text->current_line->next;
                        text->current_line->next = temp_line;
                        if( temp_line->next )
                                temp_line->next->prev = temp_line;
                        
                        if( text->last_line == text->current_line ) {
                                text->last_line = temp_line;
                                text->display_bottom_line = temp_line;
                        }
                        
                        text->num_display_lines++;
                        
                        if( text->num_display_lines > MAX_HEIGHT ) {
                                text->display_bottom_line = text->display_bottom_line->prev;
                                text->num_display_lines--;
                        }
                        
                        int temp_index = text->cursor_x;
                        temp_line->length = 0;
                        while( temp_index < text->current_line->length ) {
                                temp_line->content[temp_line->length] = text->current_line->content[temp_index];
                                temp_index++;
                                temp_line->length++;
                        }
                        text->current_line->content[text->cursor_x] = '\n';
                        text->current_line->content[text->cursor_x + 1] = '\0';
                        text->current_line->length = text->cursor_x;
                        
                        temp_line->content[temp_line->length] = '\0';
                        text->current_line = temp_line;
                          
                        text->cursor_x = 0;
                        cursor->x = 0;
                        
                        cursor->y++;
                        if( cursor->y == MAX_HEIGHT )
                                cursor->y--;
                }
        }
        /*
        text->current_line->content[text->cursor_x] = '\n';
        text->current_line->length++;
        text->current_line->content[text->current_line->length];
        text->cursor_x = 0;
*/
        
}

void addBackspace( Text *text, Cursor *cursor ) {
        /*Removes the character BEFORE the position of the cursor */
        if( text->cursor_x == 0 ) {
                if( text->current_line == text->first_line )
                        return;
                else {
                        /* If this line is actually just an overflow extension of the previous line */
                        if( text->current_line->prev->is_overflowing ) {
                                
                        }
                        /* If previous line ended with a '\n' */
                        else if( text->current_line->prev->content[text->current_line->prev->length - 1] == '\n' ) {
                                
                        }
                }
        }
        else {
                /* If the current line overflows into the next line */
                if( text->current_line->is_overflowing ) {
                        
                }
                else{
                        text->cursor_x--;
                        text->current_line->content[text->cursor_x] = ' ';
                        int temp_index = text->cursor_x;
                        while( temp_index < text->current_line->length ) {
                                text->current_line->content[temp_index] = text->current_line->content[temp_index + 1];
                                temp_index++;
                        }
                        text->current_line->length--;
                        
                        cursor->x--;
                }
        }
}

void addTab( Text *text, Cursor *cursor, int tab_chars ) {
        if( text->cursor_x >= ( MAX_WIDTH / tab_chars ) * tab_chars ) {
                
        }
        else {
                if( text->cursor_x % tab_chars == 0 ) {
                        int i;
                        for( i = 0; i < tab_chars; i++ )
                                addChar( text, cursor, ' ' );
                }
                else {
                        while( text->cursor_x % tab_chars != 0 )
                                addChar( text, cursor, ' ' );
                }
        }
}

void moveUp( Text *text, Cursor *cursor ) {
        int row, col;
        getyx( stdscr, row, col );
        if( text->current_line == text->first_line )
                return;
        else if ( text->current_line == text->display_top_line ) {
                text->display_top_line = text->display_top_line->prev;
                text->num_display_lines++;
                if( text->num_display_lines > MAX_HEIGHT )
                        text->display_bottom_line = text->display_bottom_line->prev;
                text->current_line = text->current_line->prev;
                if( col > text->current_line->length ) {
                        text->cursor_x = text->current_line->length;
                        
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row - 1, text->current_line->length );
                                cursor->y--;
                                cursor->x = text->current_line->length;
                        }
                }
                else {
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row - 1, col );
                                cursor->y--;
                        }
                }
                
                if( cursor->y < 0 )
                        cursor->y++;
        }
        else {
                text->current_line = text->current_line->prev;
                if( col > text->current_line->length ) {
                        text->cursor_x = text->current_line->length;
                        
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row - 1, text->current_line->length );
                                cursor->y--;
                                cursor->x = text->current_line->length;
                        }
                }
                else {
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row - 1, col );
                                cursor->y--;
                        }
                }
        }
        
        if( text->current_line->content[text->cursor_x - 1] == '\n' ) {
                getyx( stdscr, row, col );
                move( row, col - 1 );
                cursor->x--;
                text->cursor_x--;
        }
}

void moveDown( Text *text, Cursor *cursor ) {
        int row, col;
        getyx( stdscr, row, col );

        if( text->current_line == text->last_line )
                return;
        else if ( text->current_line == text->display_bottom_line ) {
                text->display_bottom_line = text->display_bottom_line->next;
                text->num_display_lines++;
                if( text->num_display_lines > MAX_HEIGHT )
                        text->display_top_line = text->display_top_line->next;
                text->current_line = text->current_line->next;
                if( col > text->current_line->length ) {
                        text->cursor_x = text->current_line->length;
                        
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row + 1, text->current_line->length );
                                cursor->y++;
                                cursor->x = text->current_line->length;
                        }
                }
                else {
                       if( cursor->y < MAX_HEIGHT ) {
                                move( row + 1, col );
                                cursor->y++;
                        }
                }
        }
        else {
                text->current_line = text->current_line->next;
                if( col > text->current_line->length ) {
                        text->cursor_x = text->current_line->length;
                        
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row + 1, text->current_line->length );
                                cursor->y++;
                                cursor->x = text->current_line->length;
                        }
                }
                else {
                        if( cursor->y < MAX_HEIGHT ) {
                                move( row + 1, col );
                                cursor->y++;
                        }
                }
        }
        
        if( text->current_line->content[text->cursor_x - 1] == '\n' ) {
                getyx( stdscr, row, col );
                move( row, col - 1 );
                cursor->x--;
                text->cursor_x--;
        }
}

void moveLeft( Text *text, Cursor *cursor ) {
        int row, col;
        getyx( stdscr, row, col );

        if( text->cursor_x == 0 ){
                
        }
        else {
                cursor->x--;
                text->cursor_x--;
                move( row, col - 1 );
        }
}

void moveRight( Text *text, Cursor *cursor ) {
        int row, col;
        getyx( stdscr, row, col );
        
        if( text->cursor_x == text->current_line->length ) {
                
        }
        else {
                cursor->x++;
                text->cursor_x++;
                move( row, col + 1 );
        }

        if( text->current_line->content[text->cursor_x - 1] == '\n' ) {
                getyx( stdscr, row, col );
                move( row, col - 1 );
                cursor->x--;
                text->cursor_x--;
        }
}

/* #################################################################################### */
/* Display Functions
/* #################################################################################### */

void clearDisplay( ) {
        int x, y;
        for( y = 0; y < MAX_HEIGHT; y++ ) {
                move( y, 0 );
                for( x = 0; x < MAX_WIDTH; x++ ) {
                        addch( ' ' );
                }
        }
}

void updateDisplay( Text *text, Cursor *cursor ) {
        int y = 0;
        Line *temp_line = text->display_top_line;
        while( temp_line != text->last_line && temp_line != text->display_bottom_line ) {
                move( y, 0 );
                printw( "%s", temp_line->content );
                y++;
                temp_line = temp_line->next;
        }
        move( y, 0 );
        printw( "%s", temp_line->content );
        move( cursor->y, cursor->x );
}

/* #################################################################################### */
/* Main                                                                                 */
/* #################################################################################### */

int main() {
        int ch, exit_flag, edit_flag;
        Text *text = createEmptyText( );
        Cursor cursor;
        cursor.x = cursor.y = 0;

        int tab_chars = 8;
        int iterator;
        
        initscr();
        raw();
        noecho();
        keypad( stdscr, TRUE );

        exit_flag = 0;

        while( 1 ) {
                edit_flag = 0;
                
                ch = getch( );
                
                switch( ch ) {
                        case 27:                /* Esc key */
                                exit_flag = 1;
                                break;
                        case 127:               /* Backspace key */
                                addBackspace( text, &cursor );
                                edit_flag = 1;
                                break;
                        case KEY_UP:
                                moveUp( text, &cursor );
                                break;
                        case KEY_DOWN:
                                moveDown( text, &cursor );
                                break;
                        case KEY_LEFT:
                                moveLeft( text, &cursor );
                                break;
                        case KEY_RIGHT:
                                moveRight( text, &cursor );
                                break;
                        case 9:
                                addTab( text, &cursor, tab_chars );
                                edit_flag = 1;
                                break;
                        case 10:                /* Newline */
                                addNewline( text, &cursor );
                                edit_flag = 1;
                                break;
                        default:
                                addChar( text, &cursor, ch );
                                edit_flag = 1;
                                break;
                }
                
                if( exit_flag )
                        break;
                
                if( edit_flag ) {
                        clearDisplay( );
                        updateDisplay( text, &cursor );
                        refresh( );
                }
        }
        
        cleanUp( text );
        
        endwin();
        return 0;
}
