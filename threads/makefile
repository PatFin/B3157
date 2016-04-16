all : question1.exe question2.exe question3.exe question5.exe question8.exe Question10.exe

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
	./generator.cs 20 64 50 > $@

many.txt:
	./generator.cs 1000 50 75 > $@

#########################
## program compilation

%.exe: %.c
	gcc -Wall -pthread -O4 -o $@ $^

Question10.exe : Question10.c Stockage.c Stockage.h
	gcc -Wall -pthread -O4 -o $@ Question10.c Stockage.c

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
