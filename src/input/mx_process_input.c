#include <ush.h>

static t_input *init_input() {
    t_input *input = (t_input *)malloc(sizeof(t_input));

    input->arrow_press = 0;
    input->num_backspace = 0;
    input->len = 0;
    input->command = mx_strnew(1000);//?
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

static t_dbl_list *addelem(t_dbl_list *history) {
    t_dbl_list *temp, *p;

    temp = (t_dbl_list *)malloc(sizeof(t_dbl_list));
    p = history->next; // сохранение указателя на следующий узел
    history->next = temp; // предыдущий узел указывает на создаваемый
    temp->next = p; // созданный узел указывает на следующий узел
    temp->prev = history; // созданный узел указывает на предыдущий узел
    temp->data = NULL;
    if (p != NULL)
        p->prev = temp;
    return temp;
}

static char *inside_cycle(t_input *input, int *flag, t_ush *ush, char *ret_str) {
    int k = 0;
    int i = mx_getch(input);

    while (k < i) {
        input->input_ch = input->input_ch_arr[k];
        if (input->input_ch <= 127 && input->input_ch != 27) {
            ret_str = mx_input_ascii(input, &ush->exit_status);
            if (ush->exit_status != -1)
                break;
        }
        else {
            *flag = 0;
            mx_input_non_ascii(input, ush);
        }
        if (input->input_ch < 32)
            break;
        k++;
    }
    return ret_str;
}

static char *add_history(t_input *input, int *flag, t_ush *ush, char *temp) {
    if (ush->history->data != NULL) {
        if (ush->history->next != NULL && *flag == 0) {
            *flag = 1;
            mx_strdel(&temp);
            temp = mx_strdup(ush->history->data);
        }
        mx_strdel(&ush->history->data);
    }
    ush->history->data = mx_strdup(input->command);
    return temp;
}

static void sort_history(t_ush *ush, char *temp) {
    char *p = mx_strdup(ush->history->data);

    mx_strdel(&ush->history->data);
    ush->history->data = mx_strdup(temp);
    while (ush->history->next != NULL)
        ush->history = ush->history->next;
    ush->history->data = p;
}

static void free_step(t_input *input, char *temp) {
    mx_strdel(&temp);
    mx_strdel(&input->command);
    free(input);
}

static char *read_str(struct termios savetty, t_ush *ush) {
    char *ret_str = NULL;
    char *temp = NULL;
    int flag = 0;
    t_input *input = init_input();

    input->savetty = savetty;
    input->term_width = winsize();
    while (input->input_ch != '\r' && input->ctrl_c != 1) {
        ret_str = inside_cycle(input, &flag, ush, ret_str);
        if (ush->exit_status != -1)
            break;
        temp = add_history(input, &flag, ush, temp);
    }
    if (ush->history->next != NULL)
        sort_history(ush, temp);
    free_step(input, temp);
    mx_printstr("\n");
    return ret_str;
}

char *mx_process_input(t_ush *ush) {
    char *str = NULL;
    struct termios savetty;
    //t_dbl_list *temp = NULL;
    mx_set_non_canonic(&savetty); //echo "echo 55" | ./ush
    str = read_str(savetty, ush);
//    if (*exit_status != -1)
//        return 0;
    if (ush->history->data != NULL)
        ush->history = addelem(ush->history);
    set_canonic(savetty);
    return str;
}
