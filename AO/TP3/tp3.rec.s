.section .init9
main:
	/* initialisation de l’ecran */
	call #lcd_init
	call #lcd_clear

	/* emballage des arguments */
	MOV #0, R15

	call #fact
	
	/* deballage de la valeur de retour de mult
	qu’on re-emballe comme argument pour l’appel suivant */

	
	call #lcd_display_number
	/* infinite loop */
done:
	jmp done

fact:
	PUSH R15
	CMP #1, R15
	jz finfact
	SUB #1, R15
	call #fact
	
finfact:
	POP R14
	call #mult
	MOV R13, R15
	ret


mult: 
	MOV R14, &0x0132
	MOV R15, &0x0138
	
	MOV &0x013A, R13
	
	ret

