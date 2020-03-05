APP_NAME = ush

LIBMXF = libmx

LIB_NAME = libmx.a

INC = \
inc/ \
libmx/inc/

SRC_DIR = src

OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/,\
	builds/cd.c \
	builds/ls.c \
	builds/pwd.c \
	input/mx_process_input.c \
<<<<<<< HEAD
	input/mx_input_ascii.c \
	input/mx_input_non_ascii.c \
	input/mx_set_non_canonic.c \
	input/mx_fill_command.c \
	input/mx_moving_coursor_str.c \
	parsing/mx_parsing.c \
	printing/mx_print_prompt.c \
	main/mx_create_ush.c \
	main/main.c)
=======
	main.c)
>>>>>>> 3018e9d68a5be56ec1764b16b6bf64d3de00ff7c

OBJ = \
	cd.o \
	ls.o \
	pwd.o \
<<<<<<< HEAD
	mx_process_input.o \
	mx_input_ascii.o \
	mx_input_non_ascii.o \
	mx_set_non_canonic.o \
	mx_fill_command.o \
	mx_moving_coursor_str.o \
	mx_print_prompt.o \
	mx_parsing.o \
	mx_create_ush.o \
	main.o
=======
	main.o \
	mx_process_input.o

>>>>>>> 3018e9d68a5be56ec1764b16b6bf64d3de00ff7c
CC = clang

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all : install

install : libmx/libmx.a uls

libmx/libmx.a:
	@make -C $(LIBMXF)

uls : $(SRC) inc/ush.h libmx/libmx.a
	@$(CC) $(CFLAGS) -c $(SRC) $(foreach d, $(INC), -I $d)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMXF)/$(LIB_NAME) -o $(APP_NAME)
	@printf "\r\33[2Kush \033[32;1mcreated\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)

uninstall : clean
	@make uninstall -C $(LIBMXF)
	@rm -rf $(APP_NAME)

clean :
	@make clean -C $(LIBMXF)
	@rm -rf $(OBJ_DIR)

reinstall : uninstall install