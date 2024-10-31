set -xe

gcc main.c                                            \
  -ggdb -o result.o  -lGL -lm -l:libraylib.a          \
  -I../raylib-5.0_linux_amd64/include                 \
  -L../raylib-5.0_linux_amd64/lib                     \

./result.o
