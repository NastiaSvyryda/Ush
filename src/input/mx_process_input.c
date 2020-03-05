#include <ush.h>
<<<<<<< HEAD



t_dblLinkedList *createDblLinkedList() {
    t_dblLinkedList *tmp = (t_dblLinkedList *) malloc(sizeof(t_dblLinkedList));
    tmp->head = tmp->tail = NULL;
    return tmp;
}

void deleteDblLinkedList(struct s_dblLinkedList **list) {
    t_dblLinkedNode *tmp = (*list)->head;
    t_dblLinkedNode *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}


void pushFront(t_dblLinkedList *list, void *data) {
    t_dblLinkedNode *tmp = (t_dblLinkedNode *) malloc(sizeof(t_dblLinkedNode));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->data = data;
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
}



static void init_input(t_input *input) {
    input->num_backspace = 0;
    input->len = 1;
    input->command = mx_strnew(CHAR_MAX);
    input->ctrl_c = 0;
    input->enter = 0;
    input->left = 0;
    input->coursor_position = 0;
    input->input_ch_arr = (char *)&input->input_ch;
}

static char *read_str(t_ush *ush, t_input *input) {
    char *ret_str = NULL;

    init_input(input);
    while (1) {
        read(0, &input->input_ch, 4);
        if (input->input_ch <= 127 && input->input_ch != 27)
            ret_str = mx_input_ascii(input);
        else
                mx_input_non_ascii(input, ush);
        if (input->enter == 1 || input->ctrl_c == 1)
            break;
    }
    mx_strdel(&input->command);
    free(input);
    input = NULL;
    if ( ret_str == NULL|| ret_str[0] == '\0' )
=======
#define KEYCODE_R 67
#define KEYCODE_L 68
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42

static void set_non_canonic(struct termios *savetty) {
    struct termios tty;

    if ( !isatty(0) ) {
        fprintf (stderr, "stdin not terminal\n");
        exit (1);
    }
    tcgetattr (0, &tty);
    *savetty = tty;
    tty.c_lflag   &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);
}

static void set_canonic(struct termios savetty) {
    tcsetattr (STDIN_FILENO, TCSANOW, &savetty);
}

static char *enable_noncanonic_backspace(char ch, size_t *top, char *str) {
    const char delbuf[] = "\b \b";
    char *ret_str = NULL;
    switch (ch) {
        case 127:
            if (top) {
                --(*top);
                write(STDOUT_FILENO, delbuf, strlen(delbuf));
            }
            break;
        case '\n':
            ret_str = strndup(str, *top);
            break;
        default:
            str[(*top)++] = ch;
            write(STDOUT_FILENO, &ch, sizeof ch);

            break;
    }
    return ret_str;
}

static char *read_str(char *str) {
    char ch = '\0';
    size_t top = 0;
    char *ret_str = NULL;
    int i = 0;

    str = mx_strnew(sizeof (char) * CHAR_MAX/8);
    while (1) {
        read(0, &ch,4);
        if (ch != 0 && ch != 67 && ch != 68)
            ret_str = enable_noncanonic_backspace(ch, &top, str);
        if(ch == KEYCODE_R){
            mx_printint(KEYCODE_R);
        }
        if(ch == KEYCODE_L){
            mx_printint(ch);
        }
        if  (ch == 4) { //^D
            mx_printstr("\n");
            exit(0);
        }
        else if (ch == 3) { //^C
            mx_printstr("\n");
            mx_strdel(&ret_str);
            break;
        }
        else if(ch == '\n') {
            mx_printchar('\n');
            break;
        }
        i++;
    }
    if( ret_str == NULL|| ret_str[0] == '\0' )
>>>>>>> 3018e9d68a5be56ec1764b16b6bf64d3de00ff7c
        return NULL;
    return ret_str;
}


<<<<<<< HEAD

char *mx_process_input(t_ush *ush) {
    t_input *input = (t_input *) malloc(sizeof (t_input));
    ush->history = createDblLinkedList();
    char *str = NULL;
    int history = 0;

    mx_set_non_canonic(&input->savetty);
    str = read_str(ush, input);
    mx_printstr(str);
    if (str !=  NULL) {
        history++;
        pushFront(ush->history, str);
    }
    set_canonic(input->savetty);
=======
char *mx_process_input(int *status) {// сделать обработку \ и enter перенос строки продолжение ввода
    // обработка в другом процессе () subshell
    char *str = NULL;
    status++;
    struct termios savetty;

    set_non_canonic(&savetty);
    str = read_str(str);
    set_canonic(savetty);
>>>>>>> 3018e9d68a5be56ec1764b16b6bf64d3de00ff7c
    return str;
}
