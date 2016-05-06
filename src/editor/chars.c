/* #################################################################### */
/*			REQUIRED HEADERS				*/
/* #################################################################### */

#include "editor/chars.h"
#include "editor/cursor.h"

/* #################################################################### */
/*			IMPLEMENTATION FUNCTIONS			*/
/* #################################################################### */

/* #################################################################### */
/*			INTERFACE FUNCTIONS				*/
/* #################################################################### */

void addChar( Text *t, Cursor *cursor, char c ) {
	Node *n1 = t->cur_n;		/* Get the current node */
	Node *n2 = createNode( n1->c );	/* Get a copy of the current node */
	n2->next = n1->next;
	n1->next = n2;			/* Insert the node after current node*/
	n1->c = c;			/* Change char value of current node*/

	moveRight( t, cursor );		/* Move the cursor right */
}

void addNewline( Text *t, Cursor *cursor ) {
	Node *n1 = t->cur_n;		/* Get the current node */
	Line *l1 = t->cur_l;		/* Get the current line */
	Line *l2 = insertLineAfter( l1 );

	/* If n1 is the last node in the line, it is a '\n'. */
	if( n1->c == '\n' ) {
		moveDown( t, cursor );
		return;
	}
	else {
		clearNode( l2->head );
		l2->head = n1->next;

		Node *tmp = createNode( n1->c );
		tmp->next = l2->head;
		l2->head = tmp;

		n1->c = '\n';
		n1->next = NULL;

		moveDown( t, cursor );
	}
}

void addBackspace( Text *t, Cursor *cursor ) {

}

void addTab( Text *text, Cursor *cursor ) {

}
