Mytest:main.o test.o
	gcc -o $@  $^ 
main.o:main.c
	gcc -c  $<
test.o:test.c
	gcc -c  $<
.PHONY:
	
clean:
	rm -f test.o main.o Mytest
