all : tp4.elf

%.elf : %.o lcd.o
	msp430-gcc -mmcu=msp430fg4618 -mcpu=430 -mdisable-watchdog -o $@ $^

%.o : %.c
	msp430-gcc -mmcu=msp430fg4618 -mcpu=430 -Wall -Werror -c -o $@ $^

%.o : %.s
	msp430-as -mmcu=msp430fg4618 -o $@ $^

%.lst : %.elf
	msp430-objdump -d $^ > $@
	
clean : 
	rm *.elf
	rm *.o
	
