#include <ush.h>

void mx_ush(char **input) {
    extern char **environ;

    execve("/Users/asvyryda/Desktop/Ush/ush", input, environ);//change directory
}
static int is_builtin(char *command) {
     char builtins[][10] = {"cd", "pwd", "env", "ush", "export",
                            "unset", "exit", "which", "echo"};
     char *low_com = mx_strdup(command);
     int num = 0;

     for (int i = 0; i < mx_strlen(command); i++)
         low_com[i] = (char)mx_tolower(low_com[i]);
     for (int i = 0; i < 9; i++) {
         if (mx_strcmp(builtins[i], low_com) == 0)
             num = i + 1;
     }
     mx_strdel(&low_com);
     return num;
}

static char *coomand_in_path(char *command) {
    char **path = mx_strsplit(MX_PATH(), ':');
    char *command_p = NULL;
    int paths = mx_count_arr_el(path);

    for (int i = 0; i < mx_count_arr_el(path); i++) {
        command_p = mx_strnew(mx_strlen(command) + mx_strlen(path[i]) + 1);
        mx_strcpy(command_p, path[i]);
        command_p = mx_strcat(command_p, "/");
        command_p = mx_strcat(command_p, command);
        if (mx_file_exist(command_p))
            break;
        mx_strdel(&command_p);
    }
    mx_free_void_arr((void**)path, paths);
    if (command_p == NULL)
        command_p = mx_strdup(command);
    //mx_printstr(command_p);
    return command_p;
}

static void foo(char **input) {
    pid_t pid;
    extern char **environ;
    errno = 0;
    int command = is_builtin(input[0]);
    char *command_p = NULL;
    char *output = mx_strnew(CHAR_MAX - 1);
    pid = fork();
    if (pid != 0) {
        if (command == 1)
            mx_cd(input);
        else if (command == 5)
            mx_export(input);
        else if (command == 6)
            mx_unset(input);
        else if (command == 7) {
            mx_exit(input);
        }
        wait(NULL);
    }
    else {
        if (command == 2)
            mx_pwd(input);
        else if (command == 3)
            mx_env(input);
        else if (command == 4)
            mx_ush(input);
        else if (command == 0) {
            command_p = coomand_in_path(input[0]);
            if (mx_file_exist(command_p)) {
                int exec = execve(command_p, input, environ);
                if (exec == -1 && errno == EACCES)
                    fprintf(stderr, "ush: Permission denied:%s\n", input[0]);
            }
            else
                fprintf(stderr, "ush: %s: command not found\n", input[0]);
            mx_strdel(&command_p);
        }
        mx_strdel(&output);
        exit(0);
    }
}

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


static void executing(int *status, char *str) {
    char **input = NULL;

    if (str != NULL && *status != 3) {
        input = parse_input(str, status);
        foo(input);
        mx_free_void_arr((void **)input, mx_count_arr_el(input));
    }
}

void sigint () {
    //signal(SIGINT, sigint);
    mx_printstr("\n");
}

int main(int argc, char **argv) {
    //status 0 - normal; 1 - pipe; 2 - commsub; 3 - ^C break;
    int status = 0;
    t_ush *ush = mx_create_ush(argc, argv);
    char *shlvl = mx_itoa(mx_atoi(MX_SHLVL()) + 1);

    setenv("SHLVL", shlvl, 1);
    mx_strdup(shlvl);
    while(1) {
        signal(SIGINT, sigint);
        mx_print_prompt(&ush->emodji_num);
        ush->command = mx_process_input(&status , ush);
        //mx_parsing(ush->command);
        executing(&status, ush->command);
        mx_strdel(&ush->command);
        system("leaks -q ush");
    }
    return 0;
}

