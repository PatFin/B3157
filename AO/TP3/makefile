all : tp2.elf tp2.lst tp2boutons.elf tp2lcd.elf tp2buzzer.elf

tp2lcd.elf : tp2lcd.c lcd.c
	msp430-gcc -mmcu=msp430fg4618 -mdisable-watchdog -o $@ $^

%.elf : %.c
	msp430-gcc -mmcu=msp430fg4618 -mdisable-watchdog -o $@ $^
	
%.lst : %.elf
	msp430-objdump -d $^ > $@
