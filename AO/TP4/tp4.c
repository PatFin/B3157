#include "msp430fg4618.h"
#include "lcd.h"
#include "intrinsics.h"


unsigned int cpt;


void __attribute__ ((interrupt(TIMERA0_VECTOR))) mon_traitant_interruption_timer ( void )
{
	lcd_display_number ( cpt );
	cpt ++;
}

void __attribute__ ((interrupt(PORT1_VECTOR))) traitement_interruption_bouton ( void )
{
/*
	if ( (P1IFG & ) == 1 )
	{	//Bouton 1
	
	
	}
	else
	{	//Bouton 2
	
	}
	*/
	
	lcd_clear();
	cpt = 0;
	P1IFG = 0;
	
}

int main ( void )
{
	lcd_init ( );
	lcd_clear ( );
	P5DIR |= 0x02;
	
	
	//Configuration des boutons
	P1IES = 1;
	P1IE = 3;
	
	cpt = 0;
	
	//Configuration du timer
	//Init en lecture / écriture de  Timer_A
	TACTL |= 4;
	TACCR0 |= 0x28f6;
	TACTL = 0x0210;
	TACCTL0 = 0x0010;	//Configuration pour que le timer lance des interruptions
	__eint ( );
		

	for ( ; ; )
	{
		/*
		while ( (TACTL & 1) == 0 );
		TACTL &= 0xfffe;
		mon_traitant_interrutpion_timer ( );
		*/
		volatile unsigned int i = 0;
		for ( ; i < 0xfff0; i++ )
		{
		}
		
		P5OUT = P5OUT ^ 0x02 ; 	//Toggle P5.1 (LED4)
		
	
	}	
	return 0;
}
