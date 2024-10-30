set -xe

gcc ffmpeg_linux.c main.c -ggdb -o result.o -lraylib -lGL -lm -I../raylib-5.0_linux_amd64/include -L../raylib-5.0_linux_amd64/lib/libraylib.a
./result.o

