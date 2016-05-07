/* #################################################################### */
/*			REQUIRED HEADERS				*/
/* #################################################################### */

#include "editor/cursor.h"
#include "global_variables.h"

/* #################################################################### */
/*			IMPLEMENTATION FUNCTIONS			*/
/* #################################################################### */

void scrollUp( Text *t, Cursor *cursor ) {

}

void scrollDown( Text *t, Cursor *cursor ) {

}

/* #################################################################### */
/*			INTERFACE FUNCTIONS				*/
/* #################################################################### */

void moveUp( Text *t, Cursor *cursor ) {
	Line *l = t->cur_l;
	if( l == t->first )	/* If this is the first line */
		return;
	else {
		cursor->y--;
		if( cursor->y < 0 ) {
			scrollUp( t, cursor );
		}
		t->cur_l = l->prev;
		int count = 0;
		Node *n = l->head;
		while( n && count < cursor->x ) {
			n = n->next;
		}
		t->cur_n = n;
		cursor->x = count;
		move( cursor->y, cursor->x );	}
}

void moveDown( Text *t, Cursor *cursor ) {
	Line *l = t->cur_l;
	if( l->next == NULL )	/* If this is the last line */
		return;
	else {
		cursor->y++;
		if( cursor->y >= SCREEN_HEIGHT ) {
			scrollDown( t, cursor );
		}
		t->cur_l = l->next;
		int count = 0;
		Node *n = l->head;
		while( n && n->c != '\n' && count < cursor->x ) {
			n = n->next;
		}
		t->cur_n = n;
		cursor->x = count;
		move( cursor->y, cursor->x );
	}
}

void moveRight( Text *t, Cursor *cursor ) {
	Node *n = t->cur_n;		/* Get the current node */

	/* If it is the last character */
	if( n->c == '\n' ) {
		return;
	}
	else {
		cursor->x++;
		if( cursor->x >= SCREEN_WIDTH ) {
			cursor->x = 0;
			cursor->y++;
			if( cursor->y >= SCREEN_HEIGHT ) {
				scrollDown( t, cursor );
			}
		}
		t->cur_n = t->cur_n->next;
		move( cursor->y, cursor->x );
	}
}

void moveLeft( Text *t, Cursor *cursor ) {
	Node *n = t->cur_n;

	/* If it is the first node of the line */
	if( t->cur_n == t->cur_l->head ) {
		return;
	}
	else {
		cursor->x--;
		if( cursor->x < 0 ) {
			cursor->x = SCREEN_WIDTH;
			cursor->y--;
			if(cursor->y < 0 ) {
				scrollUp( t, cursor );
			}
		}
		Node *tmp = t->cur_l->head;
		while( tmp && tmp->next != n ) {
			tmp = tmp->next;
		}
		t->cur_n = tmp;
		move( cursor->y, cursor->x );
	}
}
