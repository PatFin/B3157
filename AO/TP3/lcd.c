#include "msp430fg4618.h"
/*  Initialize the LCD_A controller
    
    claims P5.2-P5.4, P8, P9, and P10.0-P10.5
    assumes ACLK to be default 32khz (LFXT1)
*/
void lcd_init()
{
	// our LCD screen is a SBLCDA4 => 4-mux operation (cf motherboard.pdf p6)
	  
	// 4-mux operation needs all  4 common lines (COM0-COM3). COM0 has
	// its dedicated pin  (pin 52, cf datasheet.pdf p3),  so let's claim the
	// other three.
	P5DIR |= (BIT4 | BIT3 | BIT2); // pins are output direction
	P5SEL |= (BIT4 | BIT3 | BIT2); // select 'peripheral' function (VS GPIO)
	  
	// Configure LCD controller (cf msp430.pdf page 750)
	LCDACTL = 0b00011101;
	// bit 0 turns on the LCD_A module
	// bit 1 unused
	// bit 2 enables LCD segments
	// bits 3-4 set LCD mux rate: 4-mux
	// bits 5-7 set LCD frequency
	 
	// Configure port pins
	//
	// mappings  are  detailed  on motherboard.pdf p19: our  screen  has  22
	// segments, wired to MCU pins S4 to S25 (shared with GPIO P8, P9,
	// and P10.0 to P10.5)
	LCDAPCTL0 = 0b01111110;
	// bit 0: MCU S0-S3   => not connected to the screen
	// bit 1: MCU S4-S7   => screen pins S0-S3   (P$14-P$11)
	// bit 2: MCU S8-S11  => screen pins S4-S7   (P$10-P$7)
	// bit 3: MCU S12-S15 => screen pins S8-S11  (P$6 -P$3)
	// bit 4: MCU S16-S19 => screen pins S12-S15 (P$2, P$1, P$19, P$20)
	// bit 5: MCU S20-S23 => screen pins S16-S19 (P$21-P$24)
	// bit 6: MCU S24-S25 => screen pins S20-21  (P$25, P$26)
	// bit 7: MCU S28-S31 => not connected to the screen
	  
	  LCDAPCTL1 = 0 ; // MCU S32-S39 => not connected to the screen
}

void lcd_clear ( )
{
	int zone;
	for ( zone = 145; zone <= 164 ; zone ++ )
	{
		*((unsigned char*)zone) = 0;
	}
}

void lcd_fill ( )
{
	int zone;
	for ( zone = 145; zone <= 164 ; zone ++ )
	{
		*((unsigned char*)zone) = 255;
	}
}

void lcd_env ( int on )
{
	int zone = 157;
	
	char valeur = *((unsigned char*)zone);
	if ( on == 0 )
	{
		valeur = valeur | 0b00000001;
	}
	else
	{
		valeur = valeur & 0b11111110;
	}
	*((unsigned char*)zone) = valeur;
}


void lcd_num ( unsigned int position, unsigned int valeur )
{
	int zone = 147 + position;
	char code;
	switch ( valeur )
	{
		case 10:
		code = 0b00000000;
		break;
		
		case 0:
		code = 0b01011111;
		break;
		case 1:
		code = 0b00000110;
		break;
		case 2:
		code = 0b01101011;
		break;
		case 3:
		code = 0b00101111;
		break;
		case 4:
		code = 0b00110110;
		break;
		case 5 :
		code = 0b00111101;
		break;
		case 6 :
		code = 0b01111101;
		break;
		case 7:
		code = 0b00000111;
		break;
		case 8:
		code = 0b01111111;
		break;
		case 9:
		code = 0b00111111;
		break;

		default :
		code = 0b11111111;
	}
	*((unsigned char*)zone) = code;
}

void lcd_display_number ( unsigned int number )
{
	unsigned int i = 0;
	while ( number != 0 )
	{
		lcd_num ( i++ , number % 10 );
		number = number / 10 ;
	}
}

