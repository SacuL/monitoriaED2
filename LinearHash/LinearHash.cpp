#include "LinearHash.h"
#include "hash.cpp"
#include<iostream>
using namespace std;

LinearHash::LinearHash()
{
    LinearHash::LinearHash(DEFAULT_INITIAL_LEVEL,DEFAULT_MAX_BUCKET_CAPACITY);
}
/*
Note: Initial size of the hash2 table is 2^level
*/
LinearHash::LinearHash( int i_initialLevel, int i_bucketMaxCapacity )
{
	if ( i_initialLevel >= 0 )
		m_currentLevel = i_initialLevel;
	else
		m_currentLevel = DEFAULT_INITIAL_LEVEL;

	if ( i_bucketMaxCapacity > 0 )
		m_bucketMaxCapacity = i_bucketMaxCapacity;
	else
		m_bucketMaxCapacity = DEFAULT_MAX_BUCKET_CAPACITY;

	m_currentMaxBucketsBeforeSplit = twoToPowerOf(m_currentLevel + 1);

	// Allocate hash2 table
	m_hash2Table = new bucket[m_currentMaxBucketsBeforeSplit];

	// Allocate buckets of hash2 table
	for ( int i = 0 ; i < m_currentMaxBucketsBeforeSplit ; i++ )
		initNewBucketPage( m_hash2Table[i] );

	m_nextBucketIndexToSplit = 0;
}

void LinearHash::displayhash2Table( void )
{
	printf( "Level = %i\n", m_currentLevel );

	// Display all buckets up to max(last mirror bucket,range of current level)
	for ( int i = 0 ; i < m_nextBucketIndexToSplit + twoToPowerOf( m_currentLevel ) ; i++ )
	{
		if ( i == twoToPowerOf( m_currentLevel ) )
			printf( "--------------------\n" );
		printf( "%i: ", i );
		bucket * currBucketPage = &( m_hash2Table[i] );
		do
		{
			printf( "[%i", currBucketPage->page[0] );
			for ( int j = 1 ; j < m_bucketMaxCapacity ; j++ )
				printf( ",%i", currBucketPage->page[j] );
			printf( "] " );
			currBucketPage = currBucketPage->next;
		}
		while ( currBucketPage );
		printf( "\n" );
	}
}

void LinearHash::increasehash2TableLevel( int i_newhash2TableLevel )
{
	if ( i_newhash2TableLevel == m_currentLevel )
		return;

	int newMaxBucketsBeforeSplit = twoToPowerOf(i_newhash2TableLevel + 1);

	// Allocate new hash2 table
	bucket * newhash2Table = new bucket[newMaxBucketsBeforeSplit];

	// Copy old bucket pointers into new hash2 table
	for ( int i = 0 ; i < m_currentMaxBucketsBeforeSplit; i++ )
		newhash2Table[i] = m_hash2Table[i];

	// Allocate additional buckets of new hash2 table
	for ( int i = m_currentMaxBucketsBeforeSplit ; i < newMaxBucketsBeforeSplit ; i++ )
		initNewBucketPage( newhash2Table[i] );

	// De-allocate old hash2 table
	delete [] m_hash2Table;

	// Update member vars
	m_hash2Table = newhash2Table;
	m_currentLevel = i_newhash2TableLevel;
	m_currentMaxBucketsBeforeSplit = twoToPowerOf( m_currentLevel + 1 );
}

void LinearHash::insert( int i_value )
{
	// Whether or not the insert requires a split
	bool split = false;

	// Determine hash2 key of value for current level
	int key = hash2( i_value, m_currentLevel );

	printf( "Attempting to insert value %i into bucket %i\n", i_value, key );

	// If hash2 key is in [nextBucketIndexToSplit,currentLevelRange), then value goes into this bucket
	if ( key >= m_nextBucketIndexToSplit && key < twoToPowerOf(m_currentLevel) )
		LinearHash::insertToBucket( i_value, key, split );
	else
	{
		// hash2 key for current level falls into [0,nextBucketIndexToSplit)
		// See if value should go into split image by calculating next level's hash2 key
		int nextLevelKey = hash2( i_value, m_currentLevel + 1 );

		// If next level's hash2 key > last split image, then value does not go into split image (since split image does not exist)
		// Otherwise, value goes into split image
		if ( nextLevelKey > (m_nextBucketIndexToSplit - 1) + twoToPowerOf(m_currentLevel) )
			LinearHash::insertToBucket( i_value, key, split );
		else
			LinearHash::insertToBucket( i_value, nextLevelKey, split );
	}

	if ( split )
	{
		// Split next bucket and re-distribute values in both buckets
		int newMirrorImageBucketIndex = m_nextBucketIndexToSplit + twoToPowerOf(m_currentLevel);

		bucket * currBucketPage = &( m_hash2Table[m_nextBucketIndexToSplit] );
		do
		{
			for ( int i = 0 ; i < m_bucketMaxCapacity ; i++ )
			{
				if ( currBucketPage->page[i] != -1 )
				{
					// If value belongs in mirror image bucket, move it there, otherwise don't move it
					int nextLevelKey = hash2( currBucketPage->page[i], m_currentLevel + 1 );
					if ( nextLevelKey == newMirrorImageBucketIndex )
					{
						LinearHash::insertToBucket( currBucketPage->page[i], newMirrorImageBucketIndex, split );
						currBucketPage->page[i] = -1;
					}
				}
			}
			currBucketPage = currBucketPage->next;
		}
		while ( currBucketPage );

		// Compact the original bucket page that was split
		compactBucket( m_nextBucketIndexToSplit );

		printf( "Split occured! Bucket %i split to %i\n", m_nextBucketIndexToSplit, newMirrorImageBucketIndex );

		// Increment next bucket index to split
		m_nextBucketIndexToSplit++;

		// If next bucket index to split is outside of current level range,
		// increment level and set next bucket index to split back to 0
		if ( m_nextBucketIndexToSplit >= twoToPowerOf(m_currentLevel) )
		{
			increasehash2TableLevel( m_currentLevel + 1 );
			m_nextBucketIndexToSplit = 0;
			printf( "Level increased from %i to %i\n", m_currentLevel - 1, m_currentLevel );
		}

		printf( "Next bucket to split will be %i\n", m_nextBucketIndexToSplit );
	}
}

void LinearHash::insertToBucket( int i_value, int i_bucketIndex, bool & o_split )
{
	bucket * currBucketPage = &( m_hash2Table[i_bucketIndex] );
	bucket * prevBucketPage = NULL;

	// Attempt to insert to target bucket's pages
	do
	{
		for ( int i = 0 ; i < m_bucketMaxCapacity ; i++ )
		{
			if ( currBucketPage->page[i] == -1 )
			{
				currBucketPage->page[i] = i_value;
				return;
			}
		}
		prevBucketPage = currBucketPage;
		currBucketPage = currBucketPage->next;
	}
	while ( currBucketPage );

	// Bucket is full; allocate and initialize overflow page, insert value into it, and append to bucket
	currBucketPage = ( bucket * )malloc( sizeof(bucket) );
	initNewBucketPage( *currBucketPage );
	currBucketPage->page[0] = i_value;
	prevBucketPage->next = currBucketPage;

	// Indicate to caller that split is necessary
	o_split = true;
}

void LinearHash::compactBucket( int i_bucketIndex )
{
	bucket * currBucketPage = &( m_hash2Table[i_bucketIndex] );

	// Allocate and initialize new bucket (will be the compacted bucket)
	bucket compactedBucket;
	initNewBucketPage( compactedBucket );

	bucket * nextBucketPageToInsertTo = &compactedBucket;
	int nextIndexToInsertTo = 0;

	// Loop through non-compact bucket and copy elements into new bucket
	do
	{
		for ( int i = 0 ; i < m_bucketMaxCapacity ; i++ )
		{
			if ( currBucketPage->page[i] != -1 )
			{
				// If next index points beyond page capacity, allocate and initialize a new overflow page
				if ( nextIndexToInsertTo >= m_bucketMaxCapacity )
				{
					nextBucketPageToInsertTo->next = ( bucket * )malloc( sizeof(bucket) );
					nextBucketPageToInsertTo = nextBucketPageToInsertTo->next;
					initNewBucketPage( *nextBucketPageToInsertTo );
					nextIndexToInsertTo = 0;
				}
				nextBucketPageToInsertTo->page[nextIndexToInsertTo] = currBucketPage->page[i];
				nextIndexToInsertTo++;
			}
		}
		bucket * tempBucket = currBucketPage;
		currBucketPage = currBucketPage->next;

		// De-allocate non-compact bucket's page
		delete [] tempBucket->page;
	}
	while ( currBucketPage );

	m_hash2Table[i_bucketIndex] = compactedBucket;
}

void LinearHash::initNewBucketPage( bucket & o_newBucket )
{
	o_newBucket.page = new int[m_bucketMaxCapacity];
	o_newBucket.next = NULL;
	for ( int i = 0 ; i < m_bucketMaxCapacity ; i++ )
		o_newBucket.page[i] = -1;
}

LinearHash::~LinearHash()
{
	// De-allocate buckets of hash2 table
	for ( int i = 0 ; i < twoToPowerOf(m_currentLevel) ; i++ )
	{
		bucket * currentBucket = &( m_hash2Table[i] );
		do
		{
			delete [] currentBucket->page;
			currentBucket = currentBucket->next;
		}
		while ( currentBucket );
	}

	// De-allocate hash2 table
	delete [] m_hash2Table;
	m_hash2Table = NULL;
}
