CFLAGS:=\
	-Wall\
	-Wextra\
	-pedantic\
	-Wshadow\
	-Wpointer-arith\
	-Wcast-align \
	-Wwrite-strings\
	-Wmissing-prototypes\
	-Wmissing-declarations \
	-Wredundant-decls\
	-Wnested-externs\
	-Winline\
	-Wno-long-long \
	-Wconversion\
	-Wstrict-prototypes\

CC=gcc
SRC_FILES=$(wildcard ./*.c)
OBJ_FILES=$(patsubst ./%.c,./%.o,$(SRC_FILES))

build: $(OBJ_FILES)

./%.o: ./%.c
	$(CC) $(CFLAGS) $< -o $@