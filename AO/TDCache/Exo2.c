#define N 1000000000


#include <stdlib.h>
#include <stdio.h>


double v [N];


int main ( void )
{
	double sum = 0;
	unsigned int i;
	for ( i=0 ; i < N ; i++ )
	{
		sum += v [ i ];
	}
	return 0;
}
