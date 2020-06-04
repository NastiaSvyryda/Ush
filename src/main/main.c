#include <ush.h>

static void executing(t_ush *ush) {
    t_queue **queue = NULL;
    if (ush->command != NULL && strlen(ush->command) > 0) {
        queue = mx_parsing(ush->command);
        ush->return_value = mx_push_execute_queue(queue, ush);
    }
    mx_strdel(&ush->command);
    free(queue);

}

void sigint () {
    //signal(SIGINT, sigint);
    mx_printstr("\n");
}

static void set_shlvl(void) {
    char *shlvl = mx_itoa(mx_atoi(MX_SHLVL()) + 1);

    setenv("SHLVL", shlvl, 1);
    mx_strdel(&shlvl);
}

static t_dbl_list *deletelem(t_dbl_list *lst) {
    t_dbl_list *prev = lst->prev; // узел, предшествующий lst
    t_dbl_list *next = lst->next; // узел, следующий за lst
    if (prev != NULL)
        prev->next = lst->next; // переставляем указатель
    if (next != NULL)
        next->prev = lst->prev; // переставляем указатель
    mx_strdel(&lst->data);
    free(lst); // освобождаем память удаляемого элемента
    return(prev);
}
static void free_history(t_dbl_list *history) {
    while (history->next != NULL)
        history = history->next;
    while (history != NULL) {
        history = deletelem(history);
    }
}
////
//static char *process_str(void) {// сделать обработку \ и enter перенос строки продолжение ввода
//    // обработка в другом процессе () subshell
//    char *str = mx_strnew(20);
//
//    scanf("%s", str);
//    printf("%s", str);
//    return str;
//}
////
int main(int argc, char **argv){
    t_ush *ush = mx_create_ush(argc, argv);
    set_shlvl();
    while(1) {
        signal(SIGINT, sigint);
        signal(SIGTSTP, SIG_IGN);
        mx_print_prompt(ush->emodji_num);
        ush->command = mx_process_input(ush);
        executing(ush);
        mx_strdel(&ush->command);
        if (ush->exit_status != -1)
            break;
        system("leaks -q ush");
    }
    free_history(ush->history);
    mx_strdel(&ush->ush_path);
    free(ush);
    //system("leaks -q ush");
    if (ush->exit_status != -1)
        exit(ush->exit_status);
    return ush->return_value;
}
