#include <ush.h>

static char *parse_env_args(char **args, int *flag) {// 0 - no; 1 - s(priority); 2 - P; 3 - dir or --
    char *arg = NULL;
    int len = mx_count_arr_el(args);

    for (int i = 1; i < len; i++) {
        if (mx_strcmp(args[i], "--") == 0)
            *flag = 4;
        if ((*flag != mx_find_flag("iuP", args[i])) && args[i][0] == '-') {
            *flag = mx_find_flag("iuP", args[i]);
            continue;
        }
        if(mx_file_exist(args[i]) != 1 && (*flag != 2 || i > 2)) {
            if (mx_strcmp(args[i], "-u") == 0)
                fprintf(stderr, MX_ENV_US, args[i][1]);
            else
                fprintf(stderr, "env: %s: No such file or directory\n", args[i]);
        }
        else if(mx_file_exist(args[i]) == 1 && (*flag != 2 || i > 2))
            fprintf(stderr, "env: %s: Permission denied\n", args[i]);
        else if (args[i + 1] == NULL)
            arg = mx_strdup(args[i]);
    }
    return arg;
}

void mx_env(char **args) {
    extern char **environ;
    int flag = 0;
    char *arg = parse_env_args(args, &flag);
    char *temp = NULL;

    if (mx_count_arr_el(args) == 1 || (flag == 2 && arg == NULL && mx_count_arr_el(args) == 2))
        mx_print_strarr(environ, "\n");
    else if (flag == 2 && arg != NULL) {
        temp = mx_strjoin(args[2], "=");
        for (int i = 0; environ[i]!= NULL; i++) {
           if(strstr(environ[i], temp) == NULL) {
               mx_printstr(environ[i]);
               mx_printstr("\n");
           }
        }
        mx_strdel(&temp);
    }
    mx_strdel(&arg);
}

