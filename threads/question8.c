#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

#define MAX_FACTEUR	20

static pthread_t thread1;
static pthread_t thread2;

FILE * lecture;

static pthread_mutex_t mutexLecture;
static pthread_mutex_t mutexAffichage;


unsigned int get_prime_factors ( uint64_t n,uint64_t* dest )
{
	unsigned int nombreFacteurs = 0;
	while ( n % 2 == 0 )
	{
		dest [ nombreFacteurs ++] = 2;
		n = n / 2;
	}

	while ( n % 3 == 0 )
	{
		dest [ nombreFacteurs ++] = 3;
		n = n / 3;
	}

	uint64_t i = 5;
	uint64_t inc = 4;
	while ( n != 1 )
	{
		if ( n%i == 0 )
		{
			dest [ nombreFacteurs ++] = i;
			n = n / i;
		}
		else
		{
			inc = 6 - inc;
			i+= inc;
		}
	}

	return nombreFacteurs;
}

void print_prime_factors( void * ptr )
{
    uint64_t n;

	//On tente d'accéder au fichier grâce à un mutex
	pthread_mutex_lock ( &mutexLecture );

	uint64_t tableauFacteurs [ MAX_FACTEUR ];
	unsigned int i;
	while( EOF != fscanf( lecture, "%" PRIu64 "", &n) )
	{
		//On rends l'accès en lecture au fichier
		pthread_mutex_unlock ( &mutexLecture );

		//On calcule les facteurs premiers.
		unsigned int nbFacteurs = get_prime_factors ( n, tableauFacteurs );

		//On réserve l'affichage
		pthread_mutex_lock ( &mutexAffichage );

		printf("%" PRIu64 ":", n);
		for ( i=0; i < nbFacteurs; i++ )
		{
			printf( " %" PRIu64 "", tableauFacteurs [ i ] );
		}
		printf ( "\n" ),
		//On a terminé l'affichage, on en rend l'accès.
		pthread_mutex_unlock ( &mutexAffichage );
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

	lecture = fopen ( "input.txt" , "r");

	pthread_mutex_init ( &mutexLecture, NULL );
	pthread_mutex_init ( &mutexAffichage, NULL );

	pthread_create( &thread1, NULL, (void *) &print_prime_factors, NULL );
	pthread_create( &thread2, NULL, (void *) &print_prime_factors, NULL );

	pthread_join( thread1, NULL );
	pthread_join( thread2, NULL );

	pthread_mutex_destroy ( &mutexLecture );
	pthread_mutex_destroy ( &mutexAffichage );

    return 0;
}
