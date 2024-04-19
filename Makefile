

tempprog: main.o temp_functions.o
	gcc -o tempprog main.o temp_functions.o

main.o: main.c
	gcc -c main.c

temp_functions.o: temp_functions.c
	gcc -c temp_functions.c

clean:
	rm -f *.o tempprog
