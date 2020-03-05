#include <ush.h>
//struct lst_List {
//    struct lst_Link* first;
//    struct lst_Link* last;
//    unsigned int size;
//};
//
//struct lst_Link {
//    struct lst_Link* prev;
//    struct lst_Link* next;
//};
//
//struct lst_Value {
//    struct lst_Link lnk;
//
//    char* p;
//};
//
///* инициализирует lst пустым */
//void lst_init(struct lst_List* lst);
//
///* создает новый пустой список в свободной памяти */
//struct lst_List* lst_create();
//
///* удаляет все элементы списка lst */
//void lst_clear(struct lst_List* lst);
//
///* удаляет все элементы списка lst, а затем удаляет сам lst */
//void lst_destroy(struct lst_List* lst);
//
///* добавляет элемент p в конец списка lst */
//void lst_push_back(struct lst_List* lst, struct lst_Link* p);
//
///* добавляет элемент p в начало списка lst */
//void lst_push_front(struct lst_List* lst, struct lst_Link* p);
//
///* вставляет элемент q после элемента p в lst */
//void lst_insert_after(struct lst_List* lst, struct lst_Link* p, struct lst_Link* q);
//
///* вставляет элемент q перед элементом p в lst */
//void lst_insert_before(struct lst_List* lst, struct lst_Link* p, struct lst_Link* q);
//
///* удаляет элемент p из списка lst
//   возвращает указатель на узел, расположенный после узла p */
//struct lst_Link* lst_erase(struct lst_List* lst, struct lst_Link* p);
//
///* возвращает элемент, находящийся через n узлов после узла p */
//struct lst_Link* lst_get_next(struct lst_Link* p, int n);
//
///* возвращает элемент, находящийся до n узлов перед узлом p */
//struct lst_Link* lst_get_prev(struct lst_Link* p, int n);
//
///* выделяем память для значения списка */
//struct lst_Value* make_name(char* n);
//
///* находит n в списке lst. если не находит, возвращает 0 */
//struct lst_Link* lst_find(struct lst_List* lst, char* n);
//
///*/////////////////////////////////////////////////////////////////////////////////////////////*/
//
//void lst_init(struct lst_List* lst) {
//    lst->first = lst->last = 0;
//    lst->size = 0;
//}
//
//struct lst_List* lst_create() {
//    struct lst_List* lst = (struct lst_List*)malloc(sizeof(struct lst_List));
//    lst_init(lst);
//    return lst;
//}
//
//void lst_clear(struct lst_List* lst) {
//    struct lst_Link* curr = lst->first;
//
//    while(curr) {
//        struct lst_Link* next = curr->next;
//        free(curr);
//        curr = next;
//    }
//
//    lst->first = lst->last = 0;
//    lst->size = 0;
//}
//
//void lst_destroy(struct lst_List* lst) {
//    lst_clear(lst);
//    free(lst);
//}
//
//void lst_push_back(struct lst_List* lst, struct lst_Link* p) {
//    struct lst_Link* last = lst->last;
//
//    if(last) {
//        /* добавляем узел p после узла last */
//        last->next = p;
//        p->prev = last;
//    } else {
//        /* p - первый элемент */
//        lst->first = p;
//        p->prev = 0;
//    }
//
//    /* p - новый последний элемент */
//
//    lst->last = p;
//    p->next = 0;
//
//    ++lst->size;
//}
//
//void lst_push_front(struct lst_List* lst, struct lst_Link* p) {
//    struct lst_Link* first = lst->first;
//
//    if(lst->last) {
//        first->prev = p;
//        p->next = first;
//    } else {
//        /* p у нас будет первым и единственным на данный момент узлом */
//        lst->last = p;
//        p->next = 0;
//    }
//
//    lst->first = p;
//    p->prev = 0;
//
//    ++lst->size;
//}
//
//void lst_insert_after(struct lst_List* lst, struct lst_Link* p, struct lst_Link* q) {
//
//    if(lst->last == p) {
//        /* вставляем в конец */
//
//        lst->last = q;
//        q->next = 0;
//
//    } else {
//        /* после p есть как минимум еще один узел */
//        q->next = p->next;
//    }
//
//    p->next = q;
//
//    q->prev = p;
//
//    ++lst->size;
//}
//
//void lst_insert_before(struct lst_List* lst, struct lst_Link* p, struct lst_Link* q) {
//    if(lst->first == p) {
//        /* вставляем в начало */
//
//        lst->first = q;
//        q->prev = 0;
//
//    } else {
//        /* перед p есть как минимум еще один узел */
//        q->prev = p->prev;
//        p->prev->next = q;
//    }
//
//    q->next = p;
//
//    p->prev = q;
//
//    ++lst->size;
//}
//
//struct lst_Link* lst_erase(struct lst_List* lst, struct lst_Link* p) {
//    if(p == 0) return 0;
//
//    if(lst->size == 0) {
//        return 0;
//    }
//
//    --lst->size;
//
//    if(p == lst->first) {
//        if(p->next) {
//            /* next узел становится первым */
//            lst->first = p->next;
//            p->next->prev = 0;
//
//            free(p);
//            return p->next;
//
//        } else {
//            /* список становится пустым */
//
//            lst->first = lst->last = 0;
//
//            free(p);
//            return 0;
//        }
//    } else if(p == lst->last) {
//        if(p->prev) {
//            /* prev узел становится последним */
//            lst->last = p->prev;
//            p->prev->next = 0;
//
//            free(p);
//            return 0;
//
//        } else {
//            /* список становится пустым, и вообще то это условие не должно выполняться */
//
//            lst->first = lst->last = 0;
//
//            free(p);
//            return 0;
//        }
//
//    } else {
//        /* узел находится где-то между первым и последним */
//        p->next->prev = p->prev;
//        p->prev->next = p->next;
//
//        free(p);
//        return p->next;
//    }
//}
//
//struct lst_Link* lst_get_next(struct lst_Link* p, int n) {
//
//    struct lst_Link* get_next = p->next; /* указатель на след. узел */
//    n--;
//
//    if(get_next == 0) {
//        return 0;
//    }
//
//    while(n > 0){
//
//        get_next = get_next->next; /* едем дальше */
//
//        if(get_next == 0) {
//            /* мы уже достигли конца (переборщили с n) */
//
//            return 0;
//
//        }
//
//        n--;
//    }
//
//    return get_next;
//}
//
//struct lst_Link* lst_get_prev(struct lst_Link* p, int n) {
//
//    struct lst_Link* get_prev = p->prev; /* указатель на пред. узел */
//    n--;
//
//    if(get_prev == 0) {
//        return 0;
//    }
//
//    while(n > 0){
//
//        get_prev = get_prev->prev; /* едем назад */
//
//        if(get_prev == 0) {
//            /* мы уже достигли начала (переборщили с n) */
//
//            return 0;
//
//        }
//
//        n--;
//    }
//
//    return get_prev;
//}
//
//struct lst_Value* make_name(char* n) {
//    struct lst_Value* p = (struct lst_Value*)malloc(sizeof(struct lst_Value));
//    p->p = n;
//
//    return p;
//}
//
//struct lst_Link* lst_find(struct lst_List* lst, char* n) {
//    struct lst_Link* get_link = lst->first;
//
//    while(get_link) {
//
//        if(((struct lst_Value*)get_link)->p == n) {
//            return get_link;
//        }
//
//        get_link = get_link->next; /* едем дальше */
//    }
//
//    return 0;
//}
//
//int main()
//{
//    int get_count = 0;
//    struct lst_List lst_names; /* создаем список */
//    struct lst_Link* curr; /* указатель который поставим на начало для обхода списка */
//
//    lst_init(&lst_names);
//
//    /* создаем несколько объектов lst_Value и добавляем их в список */
//    lst_push_back(&lst_names,(struct lst_Link*)make_name("Saruman"));
//    lst_push_back(&lst_names,(struct lst_Link*)make_name("John"));
//    lst_push_back(&lst_names,(struct lst_Link*)make_name("David"));
//    lst_push_back(&lst_names,(struct lst_Link*)make_name("Richard"));
//    lst_push_back(&lst_names,(struct lst_Link*)make_name("Roger"));
//    lst_push_back(&lst_names,(struct lst_Link*)make_name("Nick"));
//
//    /* добавляем имя в начало */
//    lst_push_front(&lst_names,(struct lst_Link*)make_name("Gendalf"));
//
//    /* удаляем второе имя */
//    lst_erase(&lst_names,lst_get_next(lst_names.first, 1));
//
//    /* инсертим после первого имени */
//    /*lst_insert_after(&lst_names,lst_names.first, (struct lst_Link*)make_name("Test"));
//
//    lst_insert_after(&lst_names,lst_names.last, (struct lst_Link*)make_name("get123"));
//
//    lst_insert_before(&lst_names,lst_names.last, (struct lst_Link*)make_name("get123"));*/
//
//    curr = lst_names.first;
//
//    printf("size: %d\n", lst_names.size);
//
//    for(; curr != 0; curr = curr->next) {
//        get_count++;
//
//        printf("element %d: %s\n", get_count, ((struct lst_Value*)curr)->p);
//    }
//
//    printf("\n searching... \n\n");
//
//    curr = lst_find(&lst_names, "Roger");
//
//    if(curr != 0) {
//        printf("found: %s\n", ((struct lst_Value*)curr)->p);
//    }
//
//    getchar();
//
//    return 0;
//}
void lst_init(t_dbl_list* lst) {
    lst->first = lst->last = 0;
    lst->size = 0;
}

t_dbl_list* lst_create() {
    t_dbl_list *lst = (t_dbl_list*) malloc(sizeof (t_dbl_list));
    lst_init(lst);
    return lst;
}

static void foo(char **input) {
    pid_t pid;
    pid = fork();
    if (pid != 0) {
        if (strcmp(input[0], "cd") == 0)
            cd(input);
        if (strcmp(input[0], "exit") == 0)
            exit(0);
        wait(NULL);
    }
    else {
        if (strcmp(input[0], "pwd") == 0 || strcmp(input[0], "PWD") == 0)
            pwd();
        else if (strcmp(input[0], "ls") == 0 || strcmp(input[0], "LS") == 0)
            ls(input);
        exit(0);
    }
}

static int winsize(void) {
    struct winsize wins;
    int err = ioctl(0, TIOCGWINSZ, &wins);

    if (err == -1)
        return 0;
    return wins.ws_col;
}

static void check_str(char *str, int *status) {
    int win_width = winsize();

    if (mx_strlen(str) + 5 <= win_width) {
        *status = 0;
    }
    else {
        mx_print_error_basic("ush: shell deals only with one line user input\n");
    }
}

static char **parse_input(char *str, int *status) {
    char **input = NULL;

    check_str(str, status);
    if (mx_strchr(str, '\'') != NULL) {
        *status = 2;
        input = mx_strsplit(str, '\'');
        //обработка 'command' , рекурсия ?
    }
    else if (mx_strchr(str, '|') != NULL) {
        *status = 1;
        input = mx_strsplit(str, '|');
        //обработка pipe , рекурсия ?
    }
    else {
        *status = 0;
        input = mx_strsplit(str, ' ');
        //обработка стандартного ввода
    }
    return input;
}


static void executing(int *status, char *str) {
    char **input = NULL;

    if (str != NULL) {
        input = parse_input(str, status);
        foo(input);
        mx_free_void_arr((void **)input, mx_count_arr_el(input));
    }
}

void sigint () {
    //signal(SIGINT, sigint);
    mx_printstr("\n");
}

int main(int argc, char **argv){
    //status 0 - normal; 1 - pipe; 2 - commsub; 3 - ^C break;
    int status = 0;
    t_ush *ush = mx_create_ush(argc, argv);
    ush->history = lst_create();
    while(1) {
        signal(SIGINT, sigint);
        mx_print_prompt(ush->emodji_num);
        ush->command = mx_process_input(ush);
        //mx_parsing(ush->command);
        executing(&status, ush->command);
        mx_strdel(&ush->command);
    }
    return 0;
}
