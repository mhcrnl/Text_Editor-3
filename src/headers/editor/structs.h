// This header file defines the structures to be used by the editor
// 1. Node
// 2. Line
// 3. Text
// 4. Cursor
// Also defines prototypes of the related public functions

// Headers guards
#ifndef _EDITOR_STRUCTS_H_
#define _EDITOR_STRUCTS_H_

// One character. This implementation takes more space but facilitates
// linked list implementation of lines.
typedef struct node_s {
	char		c;
	struct node_s	*next;
} Node;

// One line. Basically a linked list, with a defined length and line
// number to ease display calculations (I hope). Also contains pointers
// to previous and next lines (hopefully will ease complexity).
typedef struct line_s {
	Node 		*head;
	int 		linum;
	int 		len;
	struct line_s	*prev;
	struct line_s	*next;
} Line;

// The entire buffer. Contains number of lines in the buffer, pointer
// to the current line and the node that the cursor is currently on.
// Also contains the top line in the display frame to ease display.
typedef struct text_s {
	Line	*first;
	Line	*top;
	Line	*cur_l;
	Node	*cur_n;
	int	num_lines;
} Text;

// Structure to represent the position of the Cursor. Will represent
// the LineNum and NodeNum
typedef struct {
	int	linum;
	int	node_num;
} Cursor;

// Functions prototypes.

// Function to create a new node with given character
Node *createNode( char c );

// Function to create a new line with given line number
// The new line has its first character as '\n'
Line *createLine( int linum );

// Function to insert a new line after a given line
Line *insertLineAfter( Line *l );

// Function to create a new empty buffer
Text *createText( );


#endif
