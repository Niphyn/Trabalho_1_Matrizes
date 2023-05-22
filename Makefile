libtads.a: tads/node.c tads/matriz.c tads/node.h tads/matriz.h
	gcc -g -c tads/node.c -o tads/node.o -Wall -Wno-unused-result
	gcc -g -c tads/matriz.c -o tads/matriz.o -Wall -Wno-unused-result 
	ar -crs libtads.a tads/node.o tads/matriz.o
all: libtads.a main.c
	gcc -g -o main main.c -I tads -L . -ltads -Wall -Wno-unused-result -lm
run:
	./main write.bin write.bin
val:
	valgrind  --track-origins=yes --error-limit=no ./main write.bin write.bin
clean:
	rm -f *.a *.o tads/*.o main