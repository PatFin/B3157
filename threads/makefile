QUESTION2 = question2.exe question2.1.exe question2.2.exe
QUESTION3 = question3.exe question3.1.exe question3.2.exe
QUESTION5 = question5.exe question5.1.exe question5.2.exe
QUESTION8 = question8.exe question8.1.exe question8.2.exe
QUESTION10 = Question10.1.exe Question10.2.exe Question10.3.exe Question10.4.exe Question10.5.exe Question10.6.exe Question10.7.exe Question10.8.exe

CFLAGS = -I/lib -L/lib/x86_64-linux-gnu/ -L/usr/lib/x86_64-linux-gnu/
#-DNODISPLAY
all : question1.exe $(QUESTION2) $(QUESTION3) $(QUESTION5) $(QUESTION8) $(QUESTION10)

help:
	@echo Useful targets:
	@echo "  small.txt medium.txt large.txt many.txt:  generate some input files "
	@echo "  question1 question2: compile your programs"
	@echo "  run1 run2:  run your programs through the 'time' utility"
	@echo "  clean:  delete all generated files"

#########################
# workload generation

tiny.txt:
	./generator.cs 20 20 0 > $@

small.txt:
	./generator.cs 20 32 50 > $@

medium.txt:
	./generator.cs 20 50 50 > $@

large.txt:
	./generator.cs 200 64 50 > $@

many.txt:
	./generator.cs 1000 64 30 > $@

#########################
## program compilation

%.exe: %.c
	gcc -Wall $(CFLAGS) -lm -pthread -Ofast -o $@ $^

Question%.exe : Question%.c Stockage.c Stockage.h
	gcc -Wall $(CFLAGS) -pthread -lm -Ofast -o $@ $< Stockage.c

Question10.6.exe : Question10.6.c StockageTable.c StockageTable.h
	gcc -Wall $(CFLAGS) -pthread -lm -Ofast -o $@ $< StockageTable.c

#########################
## program execution

run1: question1
	time ./question1

run2: question2
	time ./question2

#########################
## utilities

clean:
	rm -f question1 question2 tiny.txt small.txt medium.txt large.txt many.txt
