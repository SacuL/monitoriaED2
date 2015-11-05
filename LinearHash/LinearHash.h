#ifndef LINEARhash2_H_INCLUDED
#define LINEARhash2_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS  0
#define FAILURE -1

#define DEFAULT_INITIAL_LEVEL       1
#define DEFAULT_MAX_BUCKET_CAPACITY 3


extern int twoToPowerOf( int power );
extern int hash2( int value, int depth);

typedef struct bucket
{
	int * page;
	bucket * next;
}
bucket;

class LinearHash
{
public:
	LinearHash();
	LinearHash( int i_initialLevel, int i_bucketMaxCapacity );
	void displayhash2Table( void );
	void insert( int i_value );
	~LinearHash();
private:
	void increasehash2TableLevel( int i_newhash2TableLevel );
	void insertToBucket( int i_value, int i_bucketIndex, bool & o_split );
	void compactBucket( int i_bucketIndex );
	void initNewBucketPage( bucket & o_newBucket );

	bucket * m_hash2Table;
	int m_bucketMaxCapacity;
	int m_currentLevel;
	int m_currentMaxBucketsBeforeSplit;
	int m_nextBucketIndexToSplit;
};



#endif // LINEARhash2_H_INCLUDED
