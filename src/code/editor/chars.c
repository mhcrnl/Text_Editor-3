// Implementation of text-editing functions

#include "editor/chars.h"


int addChar( Text *t, Cursor *cursor, char c ) {
	Node *n = t->cur_n;
	Line *l = t->cur_l;

	// If the current node is the last node of the line,
	// it will be a '\n' character. So test for that, and
	// thus make two cases.

	// First test for absolute base case, which anyway
	// implies that there has been an error.
	if( n )
		return 1;

	if( n->c == '\n' ) {
		if( n->next )
			return 1;	// Inconsistency
		Node *tmp = createNode( '\n' );
		n->next = tmp;
		n->c = c;
		l->len++;
		return 0;
	}
	else {
		if( n->next )
			return 1;	// Inconsistency
		Node *tmp = createNode( n->c );
		tmp->next = n->next;
		n->next = tmp;
		n->c = c;
		l->len++;
		return 0;
	}
}

int addNewline( Text *t, Cursor *cursor ) {
}

int addBackspace( Text *t, Cursor *cursor ) {
}

int addTab( Text *t, Cursor *cursor ) {
}
