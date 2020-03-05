#include "ush.h"

void mx_insert_char(t_input *input, char sym, int index) {
    char temp;
    int i = mx_strlen(input->command) - index;

    input->command = realloc(input->command, mx_strlen(input->command) + 2);
    for (; i < mx_strlen(input->command) + 1; i++) {
        temp = input->command[i];
        input->command[i] = sym;
        sym = temp;
    }
    input->command[i] = '\0';
}

void mx_delete_char(t_input *input, int index) {
    int i = mx_strlen(input->command) - index;

    input->command = realloc(input->command, strlen(input->command));
    for (; i < mx_strlen(input->command) - 1; i++) {
        input->command[i] = input->command[i + 1];
    }
    input->command[i] = '\0';
}

void mx_clear_str() {
    write(STDOUT_FILENO, "\033[2K", 4);
    mx_printstr("\033[G");
    mx_print_prompt((wchar_t)128512);
}

char *mx_moving_coursor_str(int num_of_moves) {
    char *str2 = "\033[";
    char *str1 = mx_itoa(num_of_moves);
    char *temp = mx_strjoin(str1,"D");
    char *str = mx_strjoin(str2,temp);
    mx_strdel(&str1);
    mx_strdel(&temp);
    return str;
}
