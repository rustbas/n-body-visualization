set -xe

gcc main.c -ggdb -o result.o -lraylib -lGL -lm
./result.o

