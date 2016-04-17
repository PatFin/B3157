#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <math.h>

static pthread_t thread1;
static pthread_t thread2;
static pthread_mutex_t mutexLecture;

typedef struct str_thdata
{
    int thread_no;
    FILE * lecture;
} thdata;

void print_prime_factors(void * ptr)
{

	thdata *data;
    data = (thdata *) ptr;
    FILE * lecture = data -> lecture;
    uint64_t n;

	//On tente d'accéder au fichier grâce à un mutex
	pthread_mutex_lock ( &mutexLecture );

	while( EOF != fscanf( lecture, "%" PRIu64 "", &n) )
	{
		//On rends l'accès en lecture au fichier
		pthread_mutex_unlock ( &mutexLecture );
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
		while ( i * i < n )
		{
			if ( n%i == 0 )
			{
				printf(" %" PRIu64 "", i);
				n = n / i;
			}
			else
			{
				inc = 6 - inc;
				i+= inc;
			}
		}
		printf(" %" PRIu64 "\n", i );
	}
	//On rends l'accès en lecture au fichier pour que l'autre thread puisse se rendre compte aussi
	//que le fichier est terminé
	pthread_mutex_unlock ( &mutexLecture );

}

int main( void )
{
    // your code goes  here: open the text file (e.g.  with fopen() ),
    // then read each line (e.g. with fgets() ), turn it into a number
    // (e.g. with atoll() ) and then pass it to print_prime_factors.

	FILE * lecture = fopen ( "input.txt" , "r");
	thdata data;
	data.lecture = lecture;
	pthread_mutex_init ( &mutexLecture, NULL );


	pthread_create(&thread1, NULL, (void *) &print_prime_factors, &data);
	pthread_create(&thread2, NULL, (void *) &print_prime_factors, &data);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy( &mutexLecture );

    return 0;
}
