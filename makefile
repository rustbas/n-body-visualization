all:
	gcc main.c -g3 -o result.o -lraylib -lGL -lm -L ./c-numerical-methods/obj -lrunge-kutta

clean:
	rm result.o
