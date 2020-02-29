#include "ush.h"

static char *insert_char(char *str, char sym, int index) {
    char temp;
    int i = mx_strlen(str) - index;

    str = realloc(str, mx_strlen(str) + 2);
    for(; i < mx_strlen(str) + 1; i++) {
        temp = str[i];
        str[i] = sym;
        sym = temp;
    }
    str[i] = '\0';
    return str;
}

static char *enable_noncanonic_backspace(t_input *input, char *str) {
    const char delbuf[] = "\b \b";
    char *ret_str = NULL;
    //mx_printstr(str);
    switch (input->input_ch) {
        case 127:
            if (input->num_backspace && input->len > 0) {
                --input->num_backspace;
                input->len--;
                write(STDOUT_FILENO, delbuf, strlen(delbuf));
            }
            break;
        case '\r':
            ret_str = strndup(str, input->num_backspace + 1);
            input->enter = 1;
            mx_printstr("\n");
            break;
        case '\t':
            mx_printstr("\t");
            break;
        default:
            if (input->left > 0) {
                str = insert_char(str, (char) input->input_ch, input->left);
            }
            else
                str[(input->num_backspace++)] = (char) input->input_ch;
            input->len++;
            write(STDOUT_FILENO, &input->input_ch, sizeof input->input_ch);
            break;
    }
    return ret_str;
}
static void events (t_input *input) {
    if (input->input_ch == 4) { //^D
        mx_printstr("\n");
        exit(0);
    }
    else if (input->input_ch == 3) { //^C
        mx_printstr("\n");
        input->ctrl_c = 1;
    }
}

char *mx_input_ascii(t_input *input, char *str) {
    char *ret_str = NULL;
    if (input->input_ch != '\r'  && input->input_ch != '\t' && input->input_ch < 32)
        events(input);
    else {
        ret_str = enable_noncanonic_backspace(input, str); //
    }
    return ret_str;
}
