/* #################################################################### */
/*			HEADER GUARDS					*/
/* #################################################################### */

#ifndef _EDITOR_STRUCTS_H_
#define _EDITOR_STRUCTS_H_


/* #################################################################### */
/*			STRUCTS						*/
/* #################################################################### */

typedef struct node_s {
	char		c;		/* Content of the node */
	struct node_s *next;		/* Next node */
} Node;

typedef struct line_s {
	int		linum;		/* Line number */
	Node		*head;		/* First character of the line */
	struct line_s	*next;		/* Next line */
} Line;

typedef struct text_s {
	Line	*first;		/* First line in text */
	Line	*top;		/* Topmost line top be displayed */
	Line	*cur_l;		/* Current line */
	Node	*cur_n;		/* Current node */
} Text;

typedef struct {
	int	x;
	int	y;
} Cursor;

/* #################################################################### */
/*			INTERFACE FUNCTIONS				*/
/* #################################################################### */

Node *createNode( char c );
Line *createLine( int linum );
Line *insertLineAfter( Line *l );
Text *createText( );

/* #################################################################### */
/*			END HEADER					*/
/* #################################################################### */

#endif
