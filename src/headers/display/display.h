// This header file defines the functions to draw to the screen

#ifndef _DISPLAY_DISPLAY_H_
#define _DISPLAY_DISPLAY_H_

// User defined headers
#include "editor/structs.h"
#include "editor/ncurses_interface.h"
#include "editor/global_variables.h"

void displayFrame( char *win_name );
void drawText( Text *t );
void clearDisplay( );
void updateDisplay( Text *t, Cursor *cursor, char *win_name );

#endif
