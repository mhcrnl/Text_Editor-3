#ifndef _EDITOR_UTILITY_H_
#define _EDITOR_UTILITY_H_

int _strlen( char *str ) {
	int len = 0;
	while( str[len++] );
	return len;
}

#endif
