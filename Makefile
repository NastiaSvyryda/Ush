NAME = ush
SRC = src/main.c
SRCOB = main.o
INC = inc/ush.h
OBJ = obj/main.o
DIR = obj/
LIBMX = libmx
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install:
	@make -C $(LIBMX)
	@mkdir -p obj
	@clang $(CFLAGS) -c $(SRC)
	@cp $(SRCOB) $(DIR)
	@clang $(CFLAGS) -o $(NAME) $(OBJ) -L./libmx -lmx
	@rm -rf $(SRCOB)

uninstall: clean
	@rm -rf $(NAME)
	@make uninstall -C $(LIBMX)

clean:
	@rm -rf $(SRCOB)
	@rm -rf $(DIR)
	@make clean -C $(LIBMX)

reinstall: uninstall install