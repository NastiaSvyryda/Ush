#include <ush.h>

static char *read_str(char *str, t_ush *ush) {
    t_input *input = (t_input *) malloc(sizeof (t_input));
    input->num_backspace = 0;
    char *ret_str = NULL;
    input->len = 1;
    input->i = 0;

    input->ctrl_c = 0;
    input->enter = 0;
    input->left = 0;
    input->input_ch_arr = (char *)&input->input_ch;
    str = mx_strnew(sizeof (char) * CHAR_MAX / 8);
    while (1) {
        read(0, &input->input_ch, 4);
//        mx_printint(input->input_ch_arr[0]);
//        mx_printchar(' ');
//        mx_printint(input->input_ch_arr[1]);
//        mx_printchar(' ');
//        mx_printint(input->input_ch_arr[2]);
//        mx_printchar(' ');
        if (input->input_ch <= 127 && input->input_ch != 27) {
            ret_str = mx_input_ascii(input, str);
        }
        else {
                mx_input_non_ascii(input, ush);
        }
        if(input->enter == 1 || input->ctrl_c == 1) {
            break;
        }
    }
    mx_strdel(&str);
    free(input);
    input = NULL;
    if( ret_str == NULL|| ret_str[0] == '\0' )
        return NULL;
    return ret_str;
}



char *mx_process_input(int *status, t_ush *ush) {// сделать обработку \ и enter перенос строки продолжение ввода
    // обработка в другом процессе () subshell
    char *str = NULL;
    status++;
    int history = 0;
    struct termios savetty;

    mx_set_non_canonic(&savetty);
    str = read_str(str, ush);
    if (str !=  NULL) {
        history++;
        mx_push_front(&ush->history, str);
    }
    set_canonic(savetty);

    return str;
}
