#include <ush.h>



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
        return NULL;
    return ret_str;
}



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
    return str;
}
