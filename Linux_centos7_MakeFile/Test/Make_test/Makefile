Mytest:test.o
	gcc -o Mytest test.c
test.o:test.s
	gcc -c test.s -o test.o
test.s:test.i
	gcc -S test.i -o test.s
test.i:test.c
	gcc -E test.c -o test.i

.PHONY:clean

clean:
	rm -f test.o test.s test.i Mytest 

