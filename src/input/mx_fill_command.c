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
    input->command = mx_realloc(input->command, strlen(input->command));
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

static void case_backspace(t_input *input, t_ush *ush) {
    input->coursor_position--;
    input->len--;
    mx_clear_str();
    if (input->term_width > input->len + 8)
        mx_print_prompt(0, ush);
    mx_delete_char(input, input->coursor_position);
    if (input->term_width > input->len + 8) {
        mx_printstr(input->command);
        if (input->coursor_position != input->len)
            moving_coursor_on_n_moves(input->len - input->coursor_position, "D");
    }
//    else {
//        //mx_clear_str();
//        write(2, "ush: input string is too long", mx_strlen("ush: input string is too long"));
//        for (int i = input->term_width - 7; i < input->len; i++)
//            mx_printchar(input->command[i]);
//        if (input->term_width - 8 == input->len) {
//            moving_coursor_on_n_moves(input->term_width, "C");
//            mx_printstr("\033[A");
//            write(STDOUT_FILENO, "\033[K", 4);
//        }
//
//    }
}

static void case_default(t_input *input, t_ush *ush) {
    if (input->len + 8 > input->term_width) {
        write(2, "\nush: input string is too long", mx_strlen("ush: input string is too long"));
        input->term_width = 0;
    }
    else {
        if (input->coursor_position != input->len)
            mx_insert_char(input, input->input_ch, input->coursor_position);
        else if (input->command != NULL)
            input->command[input->len] = (char) input->input_ch;
        else {
            input->command = mx_strnew(1000);//?
            input->command[input->len] = (char) input->input_ch;
        }
        input->len++;
        input->coursor_position++;
        if (input->coursor_position != input->len) {
            mx_clear_str();
            mx_print_prompt(0, ush);
            mx_printstr(input->command);
            moving_coursor_on_n_moves(input->len - input->coursor_position, "D");
        } else
            mx_printchar((char) input->input_ch);
    }
}

char *mx_fill_command(t_input *input, t_ush *ush) {
    char *ret_str = NULL;

    switch (input->input_ch) {
        case MX_BACKSPACE:
            if (input->coursor_position > 0)
                case_backspace(input, ush);
            break;
        case MX_ENTER:
            input->enter = 1;
            ret_str = mx_strtrim(input->command);
            break;
        default:
            case_default(input, ush);
            break;
    }
    return  ret_str;
}

