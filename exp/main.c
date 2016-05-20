#include "ncurses_interface.h"
#include "definitions.h"

int main( ) {
	initNcurses( );

	int key;
	int was_ctrl = False, was_meta = False, was_key = False, was_esc = False, was_return = False, was_back = False;


	World *world = createNewWorld( );
	Buffer *buffer = createStartBuffer( );
	addBuffer( world, buffer );

}
