#include "ush.h"

static void backspace(t_input *input) {
    if (input->num_backspace >= 1 && input->len > 0
        && input->coursor_position > 0) {
        input->coursor_position--;
        input->num_backspace--;
        input->len--;
        mx_clear_str();
        mx_delete_char(input, input->left + 1);
        mx_printstr(input->command);
        if (input->left > 0 && input->num_backspace >= 1) {
            char *moving_str = mx_moving_coursor_str(input->left);
            mx_printstr(moving_str);
        }
    }
}

static void fill_str(t_input *input) {
    char *moving_str = NULL;

    if (input->left > 0) {
        mx_insert_char(input, (char) input->input_ch, input->left);
        input->num_backspace++;
    }
    else
        input->command[(input->num_backspace++)] = (char) input->input_ch;
    input->len++;
    input->coursor_position++;
    if (input->left == 0)
        write(STDOUT_FILENO, &input->input_ch, sizeof input->input_ch);
    else {
        mx_clear_str();
        mx_printstr(input->command);
        moving_str = mx_moving_coursor_str(input->left);
        mx_printstr(moving_str);
        mx_strdel(&moving_str);
    }
}

char *mx_fill_command(t_input *input) {
    char *ret_str = NULL;
    switch (input->input_ch) {
        case 127:
            backspace(input);
            break;
        case '\r':
            input->ret_str = strndup(input->command, input->num_backspace + 1);
             ret_str = mx_strtrim(input->ret_str);
            mx_strdel(&input->ret_str);
            input->enter = 1;
            mx_printstr("\n");
            break;
        case '\t':
            break;
        default:
            fill_str(input);
            break;
    }
    return ret_str;
}
