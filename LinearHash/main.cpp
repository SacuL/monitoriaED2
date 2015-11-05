/*
Linear hash2ing Example

Author: Johnson Wong

This is just a quick example I wrote up to help myself and others to understand how linear hasing works.
Starting with an empty hash2 table, you can insert more elements into it and the program
will display the contents of the hash2 table after each step.

In this example, here are some definitions:
- Empty slots in a page are indicated by -1.
- The level of the table determines how many buckets are in the table: numBuckets = level^2
- The size of memory allocated for the hash2 table at a given point in time is 2^(level+1) (in order to have space for split image buckets).
- When inserting elements into the hash2 table, overflow pages are created when existing pages in a bucket are full.
- A split is triggered whenever a new overflow page needs to be created.
- A dashed line will indicate the boundary between the original buckets for the hash2 table at the current level, and split image buckets.

In main(), a new hash2 table is created with a default initial level and max bucket capacity.
Feel free to change those values as you see fit.

Note: elements to insert must be integers >= 0.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "LinearHash.h"

using namespace std;

int main( int argc, char *argv[] )
{
	LinearHash * lh = new LinearHash(DEFAULT_INITIAL_LEVEL,DEFAULT_MAX_BUCKET_CAPACITY );

	lh->displayhash2Table();

	int value;
	while (1)
	{
		cout << "Insert: ";
		cin >> value;
		if ( value < 0 ) break;
		lh->insert( value );
		lh->displayhash2Table();
	}

	delete lh;
	lh = NULL;

	return 0;

	/* Testing:
	while (1)
	{
		cout << "Value: ";
		int value;
		cin >> value;
		cout << "Depth: ";
		int depth;
		cin >> depth;
		if (value < 0 || depth < 0) return 0;
		cout << hash2(value,depth) << endl;
	}*/

	/* Testing:
	while (1)
	{
		int power;
		cin >> power;
		if (power < 0) return 0;
		cout << "Power: " << twoToPowerOf(power) << endl;
	}*/
}

