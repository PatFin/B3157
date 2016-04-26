
#include <stdlib.h>
#include <stdio.h>


double A [N][N];
double B [N][N];
double C [N][N];


int main ( void )
{
	double sum;
	unsigned int i,j,k;
	
	for ( i=0 ; i < N ; i++ )
	{
		for ( k=0; k < N ; k ++ )
		{
			sum = A[k][j];
			for ( j = 0; j < N; j++ )
				C[i][j]+=B[i][k]*sum;
//				sum += A[i][k]*B[k][j];
				
			//			C[i][j]=sum;
		}	
	}	
	return 0;
}
