#include <ush.h>

static t_env *parse_env_args(char **args) {// 0 - no; 1 - s(priority); 2 - P; 3 - dir or --
    t_env *env = malloc(sizeof(t_env));
    int len = mx_count_arr_el(args);
    char *temp = NULL;
    extern char **environ;

    env->flag = 0;
    env->comm = NULL;
    for (int i = 1; i < len; i++) {
        if (mx_strcmp(args[i], "--") == 0)
            env->flag = 4;
        if (args[i][0] == '-') {
            if (mx_find_flag("Piu", args[i]) == 0) {
                fprintf(stderr, MX_ENV_IL, args[i][1]);
                break;
            }
            else if (mx_find_flag("Piu", args[i]) < 3 && env->flag == 0 && args[i + 1] == NULL) {
                fprintf(stderr, MX_ENV_US, args[i][1]);
                break;
            }
            else if (mx_find_flag("Piu", args[i]) > env->flag) {
                env->flag = mx_find_flag("Piu", args[i]);
                continue;
            }
            continue;
        }
        if(mx_file_exist(args[i]) != 1 && (env->flag != 3 || i > 2)) {
            fprintf(stderr, "env: %s: No such file or directory\n", args[i]);
            break;
        }
        else if(mx_file_exist(args[i]) == 1 && (env->flag != 3 || i > 2) && env->flag !=1) {
            fprintf(stderr, "env: %s: Permission denied\n", args[i]);
            break;
        }
        else if (args[i + 1] == NULL && env->flag == 3) {
            env->env_var = malloc(sizeof(char*));
            temp = mx_strjoin(args[i], "=");
            for (int i = 0, y = 0; environ[i]!= NULL; i++) {
                if(strstr(environ[i], temp) == NULL) {
                    //realloc
                    env->env_var[y] = mx_strdup(environ[i]);
                    y++;
                }
            }
            mx_strdel(&temp);
        }
    }
    return env;
}

int mx_env(char **args) {
    t_env *env = parse_env_args(args);
    char *temp = NULL;
    int return_ = 0;

    if (mx_count_arr_el(args) == 1 || env->comm == NULL)
        mx_print_strarr(env->env_var, "\n");
//    else if (flag == 2 && arg != NULL) {
//        temp = mx_strjoin(args[2], "=");
//        for (int i = 0; environ[i]!= NULL; i++) {
//           if(strstr(environ[i], temp) == NULL) {
//               mx_printstr(environ[i]);
//               mx_printstr("\n");
//           }
//        }
//        mx_strdel(&temp);
//    }
    else
        return_ = 1;
    free(env);
    return return_;
}

