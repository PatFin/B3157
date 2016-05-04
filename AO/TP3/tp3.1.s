.section .init9
main:
	/* initialisation de l’ecran */
	call #lcd_init
	call #lcd_clear

	/* emballage des arguments */
	
	PUSH #0x01
	PUSH #0x02
	PUSH #0x03
	
	POP R15
	call #lcd_display_number
	
	
	/* infinite loop */
done:
	jmp done

