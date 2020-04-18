#include "ush.h"

void mx_insert_char(t_input *input, char sym, int index) {
    char temp;

    input->command = realloc(input->command, mx_strlen(input->command) + 2);
    for (; index < mx_strlen(input->command) + 1; index++) {
        temp = input->command[index];
        input->command[index] = sym;
        sym = temp;
    }
    input->command[index] = '\0';
}


void mx_delete_char(t_input *input, int index) {
    input->command = realloc(input->command, strlen(input->command));
    for (; index < mx_strlen(input->command) - 1; index++) {
        input->command[index] = input->command[index + 1];
    }
    input->command[index] = '\0';
}

void mx_clear_str() {
    write(STDOUT_FILENO, "\033[2K", 4);
    mx_printstr("\033[G");
}

static void moving_coursor_on_n_moves(int num_of_moves, char *side) {
    char *str2 = "\033[";
    char *str1 = mx_itoa(num_of_moves);
    char *temp = mx_strjoin(str1,side);
    char *str = mx_strjoin(str2,temp);
    mx_strdel(&str1);
    mx_strdel(&temp);
    str[mx_strlen(str) + 1] = '\0';
    mx_printstr(str);
    mx_strdel(&str);
}

char *mx_fill_command(t_input *input) {
    char *ret_str = NULL;

    switch (input->input_ch) {
        case MX_BACKSPACE:
            if (input->coursor_position > 0) {
                input->coursor_position--;
                input->len--;
                mx_clear_str();
                if (input->term_width > input->len + 8)
                    mx_print_prompt((wchar_t)128512);
                mx_delete_char(input, input->coursor_position);
                if (input->term_width > input->len + 8) {
                    mx_printstr(input->command);
                    if (input->coursor_position != input->len) {
                        moving_coursor_on_n_moves(input->len - input->coursor_position, "D");
                    }
                }
                else {
                    for (int i = input->term_width - 7; i < input->len; i++) {
                        mx_printchar(input->command[i]);
                    }
                    if (input->term_width - 8 == input->len) {
                        moving_coursor_on_n_moves(input->term_width, "C");
                        mx_printstr("\033[A");
                        write(STDOUT_FILENO, "\033[K", 4);
                    }
                }
            }
            break;
        case MX_ENTER:
            input->enter = 1;
            ret_str = mx_strtrim(input->command);
            break;
        default:
            if (input->coursor_position != input->len)
                mx_insert_char(input, input->input_ch, input->coursor_position);
            else
                input->command[input->len] = (char)input->input_ch;
            input->len++;
            input->coursor_position++;
            if (input->coursor_position != input->len) {
                mx_clear_str();
                mx_print_prompt((wchar_t)128512);
                mx_printstr(input->command);
                moving_coursor_on_n_moves(input->len - input->coursor_position, "D");
            }
            else
                mx_printchar((char) input->input_ch);
            break;
    }
    return  ret_str;
}

