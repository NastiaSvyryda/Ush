#include <ush.h>

static int winsize(void) {
    struct winsize wins;
    int err = ioctl(0, TIOCGWINSZ, &wins);//заменить запрет функция

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


static int executing(int *status, char *str) {
    char **input = NULL;
    int return_value = 0;
    if (str != NULL) {
        input = parse_input(str, status);
        return_value = mx_execute(input);
        mx_free_void_arr((void **)input, mx_count_arr_el(input));
    }
    return return_value;
}

void sigint () {
    //signal(SIGINT, sigint);
    mx_printstr("\n");
}

int main(int argc, char **argv){
    //status 0 - normal; 1 - pipe; 2 - commsub; 3 - ^C break;
    int status = 0;
    t_ush *ush = mx_create_ush(argc, argv);
    char *shlvl = mx_itoa(mx_atoi(MX_SHLVL()) + 1);
    int return_value = 0;

    setenv("SHLVL", shlvl, 1);
    mx_strdup(shlvl);
    while(1) {
        signal(SIGINT, sigint);
        mx_print_prompt(ush->emodji_num);
        ush->command = mx_process_input(ush);
        //mx_parsing(ush->command);
        return_value = executing(&status, ush->command);
        mx_strdel(&ush->command);
        system("leaks -q ush");
    }
    return 0;
}
