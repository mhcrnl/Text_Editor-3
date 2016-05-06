/* #################################################################### */
/*			HEADER GUARDS					*/
/* #################################################################### */

#ifndef _EDITOR_UTILITY_H_
#define _EDITOR_UTILITY_H_

/* #################################################################### */
/*			REQUIRED INCLUDES				*/
/* #################################################################### */

#include "editor/structs.h"

/* #################################################################### */
/*			INTERFACE FUNCTIONS				*/
/* #################################################################### */

void clearNode( Node *n ) {
	free( n );
}

void clearLine( Line *l ) {
	Node *n1 = l->head;
	Node *n2 = n1;

	while( n1 ) {
		n1 = n1->next;
		free( n2 );
		n2 = n1;
	}

	free( l );
}

void clearText( Text *t ) {
	Line *l1 = t->first;
	Line *l2 = l1;

	while( l1 ) {
		l1 = l1->next;
		clearLine( l2 );
		l2 = l1;
	}

	free( t );
}

/* #################################################################### */
/*			END HEADER					*/
/* #################################################################### */

#endif