#include "LinearHash.h"

/*
Returns 2^power
*/
int twoToPowerOf( int power )
{
	int result = 1;
	for ( power-- ; power >= 0 ; power-- )
	{
		result <<= 1;
	}
	return result;
}

/*
Determines the linear hash2 key of a given value using a given depth.
Returns the "depth" least-significant bits.
Ex.
If value is 00110101 in binary, and depth is 1, hash2 will return 1 (the least significant bit).
If the depth is 4, hash2 will return 0101=3, the 4 least significant bits.
*/
int hash2( int value, int depth)
{
	if ( value < 0 || depth < 0 )
		return FAILURE;
	if ( value == 0 || depth == 0 )
		return 0;

	int key = 0;

	for ( depth-- ; depth >= 0 ; depth-- )
	{
		key <<= 1;
		if ( value & (1 << depth) )
			key++;
	}

	return key;
}
