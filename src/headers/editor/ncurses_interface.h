// Interface to interact with all NCurses calls
#ifndef _EDITOR_NCURSES_INTERFACE_H_
#define _EDITOR_NCURSES_INTERFACE_H_

#include <ncurses.h>
#include "editor/global_variables.h"

void initNcurses( );

void getDimensions( );

void endNcurses( );

#endif
