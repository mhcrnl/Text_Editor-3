/* #################################################################### */
/*			REQUIRED HEADERS				*/
/* #################################################################### */

#include <stdlib.h>
#include "editor/structs.h"

/* #################################################################### */
/*			IMPLEMENTATION FUNCTIONS			*/
/* #################################################################### */

/* #################################################################### */
/*			INTERFACE FUNCTIONS				*/
/* #################################################################### */

Node *createNode( char c ) {
	Node *n = ( Node* ) malloc( sizeof( Node ) );
	n->c = c;
	n->next = NULL;
	return n;
}

Line *createLine( int linum ) {
	Line *l = ( Line* ) malloc( sizeof( Line ) );
	l->linum = linum;
	l->head = createNode( '\n' );
	l->next = NULL;
	return l;
}

Line *insertLineAfter( Line *l ) {
	Line *new = ( Line* ) malloc( sizeof( Line ) );

	new->linum = l->linum + 1;
	new->head = createNode( '\n' );
	new->next = l->next;
	l->next = new;

	Line *tmp = new->next;
	while( tmp ) {
		tmp->linum++;
		tmp = tmp->next;
	}

	return new;
}

Text *createText( ) {
	Text *t = ( Text* ) malloc( sizeof( Text ) );
	t->first = createLine( 1 );
	t->top = t->first;
	t->cur_l = t->first;
	t->cur_n = t->first->head;
	return t;
}
