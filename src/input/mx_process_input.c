#include <ush.h>

void lst_push_front1(t_dbl_list * lst, t_dbl_node *p) {
    t_dbl_node* first = lst->first;

    if(lst->last) {
        first->prev = p;
        p->next = first;
    } else {
        /* p у нас будет первым и единственным на данный момент узлом */
        lst->last = p;
        p->next = 0;
    }

    lst->first = p;
    p->prev = 0;

    ++lst->size;
}

void lst_push_back(t_dbl_list * lst, t_dbl_node * p) {
    t_dbl_node* last = lst->last;

    if(last) {
        /* добавляем узел p после узла last */
        last->next = p;
        p->prev = last;
    } else {
        /* p - первый элемент */
        lst->first = p;
        p->prev = 0;
    }

    /* p - новый последний элемент */

    lst->last = p;
    p->next = 0;

    ++lst->size;
}



t_dbl_data* make_node(char* n) {
    t_dbl_data* p = (t_dbl_data *) malloc(sizeof (t_dbl_data));
    p->data = mx_strdup(n);

    return p;
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
    char *str = NULL;
    int history = 0;
    //int get_count = 0;//
    mx_set_non_canonic(&input->savetty);
    str = read_str(ush, input);
    if (str !=  NULL) {
        lst_push_front1(ush->history, (t_dbl_node *) make_node(str));
        history++;
    }
    ush->curr_history = ush->history->first;
//    for(; ush->curr_history != 0; ush->curr_history = ush->curr_history->next) {
//        get_count++;
//
//        printf("element %d: %s\n", get_count, ((t_dbl_data*)ush->curr_history)->data);
//    }
    set_canonic(input->savetty);
    return str;
}
