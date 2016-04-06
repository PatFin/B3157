#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

static pthread_t thread1;
static pthread_t thread2;

typedef struct str_thdata
{
    int thread_no;
    uint64_t n;
} thdata;

void print_prime_factors(void * ptr)
{
	thdata *data;
    data = (thdata *) ptr;
    uint64_t n = data -> n;

	printf("%" PRIu64 ":", n);
    // your code goes here: print "n", a colon, and then the prime factors

	while ( n % 2 == 0 )
	{
		printf ( " 2" );
		n = n / 2;
	}

	while ( n % 3 == 0 )
	{
		printf ( " 3" );
		n = n / 3;
	}

	uint64_t i = 5;
	uint64_t inc = 4;
	while ( n != 1 )
	{
		if ( n%i == 0 )
		{
			printf(" %" PRIu64 "", i);
			n = n / i;
		}
		else
		{
			inc = 6 - inc;
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
	thdata data1, data2;
	uint64_t * nombre = malloc ( sizeof ( uint64_t ) );
	uint64_t * nombre2 = malloc ( sizeof ( uint64_t ) );
	while ( EOF != (fscanf ( lecture, "%" PRIu64 "", nombre ) ) && EOF != (fscanf ( lecture, "%" PRIu64 "", nombre2 ) ) )
	{
		data1.n = *nombre;
		data2.n = *nombre2;

		pthread_create(&thread1, NULL, (void *) &print_prime_factors, &data1);
		pthread_create(&thread1, NULL, (void *) &print_prime_factors, &data2);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	}
    return 0;
}
