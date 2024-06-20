set -xe

gcc ffmpeg_linux.c main.c -ggdb -o result.o -lraylib -lGL -lm
./result.o

