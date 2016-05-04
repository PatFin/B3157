all : tp3.elf tp3.1.elf tp3.rec.elf sum.elf

%.elf : %.o lcd.o
	msp430-gcc -mmcu=msp430fg4618 -mdisable-watchdog -o $@ $^

%.o : %.c
	msp430-gcc -mmcu=msp430fg4618 -Wall -Werror -O1 -c -o $@ $^

%.o : %.s
	msp430-as -mmcu=msp430fg4618 -o $@ $^

%.lst : %.elf
	msp430-objdump -d $^ > $@
