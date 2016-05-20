// Functions for the manipulations of text in the text editor

#ifndef _EDITOR_CHARS_H_
#define _EDITOR_CHARS_H_

#include "editor/structs.h"

int addChar( Text *t, Cursor *cursor, char c );
int addNewline( Text *t, Cursor *cursor );
int addBackspace( Text *t, Cursor *cursor );
int addTab( Text *t, Cursor *cursor );

#endif
