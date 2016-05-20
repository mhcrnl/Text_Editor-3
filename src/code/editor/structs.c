// Library headers
#include <stdlib.h>

// Project headers
#include "editor/structs.h"

// Implementation of public functions

Node *createNode( char c ) {
	Node *n = ( Node* ) malloc( sizeof( Node ) );
	n->c = c;
	n->next = NULL;
	return n;
}

Line *createLine( int linum ) {
	Line *l = ( Line* ) malloc( sizeof( Line ) );
	l->head = createNode( '\n' );
	l->linum = linum;
	l->len = 0;
	l->prev = NULL;
	l->next = NULL;
	return l;
}

Line *insertLineAfter( Line *l ) {
	Line *l2 = createLine( l->linum + 1 );
	l2->prev = l;
	l2->next = l->next;
	l->next = l2;

	Line *tmp = l2->next;
	while( tmp != NULL ) {
		tmp->linum++;
		tmp = tmp->next;
	}

	return l2;
}

Text *createText( ) {
	Text*t = ( Text* ) malloc( sizeof( Text ) );
	t->first = createLine( 1 );
	t->top = t->first;
	t->cur_l = t->first;
	t->cur_n = t->first->head;
	t->num_lines = 1;
	return t;
}
