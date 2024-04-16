all:
	gcc main.c -o result.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm result.o
