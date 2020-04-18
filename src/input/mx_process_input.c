#include <ush.h>

static t_input *init_input() {
    t_input *input = malloc(sizeof(t_input));

    input->arrow_press = 0;
    input->num_backspace = 0;
    input->len = 0;
    input->command = mx_strnew(1000);
    input->ctrl_c = 0;
    input->enter = 0;
    input->coursor_position = 0;
    input->input_ch = '\0';
    input->input_ch_arr = (char *)&input->input_ch;
    return input;
}

static int mx_getch(t_input *input) {
    int size = 0;

    size = read(0, &input->input_ch, 4);
    return size;
}

//int mx_get_twidth() {
//    if (tgetent(NULL, "xterm-256color") < 0) {
//        fprintf(stderr, "ush: Could not access the termcap data base.\n");
//        exit(1);
//    }
//    return tgetnum("co");
//}
static int winsize(void) {
    struct winsize wins;
    int err = ioctl(0, TIOCGWINSZ, &wins);//заменить запрет функция

    if (err == -1)
        return 0;
    return wins.ws_col;
}

static char *read_str() {
    int i = 0;
    int k = 0;
    char *ret_str = NULL;
    t_input *input = init_input();
    input->term_width = winsize();
    while (input->input_ch != '\r') {
        k = 0;
        i = mx_getch(input);
        while (k < i) {
            input->input_ch = input->input_ch_arr[k];
            if (input->input_ch <= 127 && input->input_ch != 27) {
                ret_str = mx_input_ascii(input);
            }
            else
                mx_input_non_ascii(input);
            if (input->input_ch < 32)
                break;
            k++;
        }
    }
//    ret_str = mx_strdup(input->command);
    mx_strdel(&input->command);
    free(input);
    mx_printstr("\n");
    return ret_str;
}

char *mx_process_input() {
    char *str = NULL;
    struct termios savetty;
    mx_set_non_canonic(&savetty);
    str = read_str();
    set_canonic(savetty);

    return str;
}
