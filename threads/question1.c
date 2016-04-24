#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>

void print_prime_factors(uint64_t n)
{
	printf("%" PRIu64 "\n", n);
	printf(":");
    // your code goes here: print "n", a colon, and then the prime factors
	uint64_t i = 2;
	while ( n != 1 )
	{
		if ( n%i == 0 )
		{
			printf(" ");
			printf("%" PRIu64 "", i);
			n = n / i;
		}
		else
		{
			i++;
		}
	}
	printf("\n");
}

int main(void)
{
    print_prime_factors(77); // expected result:   77: 7 11
    print_prime_factors(84); // expected result:   84: 2 2 3 7

    // expected result:   429496729675917: 3 18229 7853726291
    //print_prime_factors(42949672);

	uint64_t blop = 0; // pow ( 2, 63 );
	uint64_t ordre = __builtin_clzll ( blop );

	printf("%" PRIu64 " : %" PRIu64"\n", blop, ordre );

    return 0;
}
