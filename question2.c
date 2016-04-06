#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void print_prime_factors(uint64_t n)
{
	printf("%" PRIu64 ":", n);
    // your code goes here: print "n", a colon, and then the prime factors
	uint64_t i = 2;
	while ( n != 1 )
	{
		if ( n%i == 0 )
		{
			printf(" %" PRIu64 "", i);
			n = n / i;
		}
		else
		{
			i++;
		}
	}
	printf("\n");
}

int main( void )
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.

	FILE * lecture = fopen ( "large.txt" , "r");

	uint64_t * nombre = malloc ( sizeof ( uint64_t ) );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", nombre ) ) )
	{
		print_prime_factors ( * nombre );
	}
    return 0;
}
