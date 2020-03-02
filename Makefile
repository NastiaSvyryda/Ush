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
	input/mx_input_ascii.c \
	input/mx_input_non_ascii.c \
	input/mx_set_non_canonic.c \
	parsing/mx_parsing.c \
	parsing/mx_count_queue_operation.c \
	parsing/mx_create_queue.c \
	parsing/mx_push_back_queue.c \
	parsing/mx_insort_t_queue.c \
	printing/mx_print_prompt.c \
	main/mx_create_ush.c \
	main/main.c)

OBJ = \
	cd.o \
	ls.o \
	pwd.o \
	mx_process_input.o \
	mx_input_ascii.o \
	mx_input_non_ascii.o \
	mx_set_non_canonic.o \
	mx_print_prompt.o \
	mx_parsing.o \
	mx_count_queue_operation.o \
    mx_create_queue.o \
    mx_push_back_queue.o \
    mx_insort_t_queue.o \
	mx_create_ush.o \
	main.o
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