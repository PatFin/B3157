.section .init9
main:
	/* initialisation de l’ecran */
	call #lcd_init
	call #lcd_clear

	/* emballage des arguments */
	MOV #6, R15
	MOV #7, R14
	call #mult
	/* deballage de la valeur de retour de mult
	qu’on re-emballe comme argument pour l’appel suivant */
	MOV R13, R15
	
	call #lcd_display_number
	/* infinite loop */
done:
	jmp done

mult: 
	MOV R14, &0x0132
	MOV R15, &0x0138
	
	MOV &0x013A, R13
	
	ret

/*
mult:
	MOV #0, R13
	MOV #0, R12
boucle:
	CMP R12,R15	
	jz  fin
	ADD #1, R12
	ADD R14, R13
	jmp boucle
fin :
	ret
	*/
