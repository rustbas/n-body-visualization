set -xe

gcc main.c ../raylib-5.0_linux_amd64/lib/libraylib.a  \
  -ggdb -o result.o  -lGL -lm                         \
  -I../raylib-5.0_linux_amd64/include                 \
  -L../raylib-5.0_linux_amd64/lib/                    \

./result.o

