Proc: proc.o main.o
	gcc -o $@ $^
proc.o:proc.c
	gcc -c  $<
main.0:main.c
	gcc -c $<

.PHONY:clean

clean:
	rm -f Proc *.o



