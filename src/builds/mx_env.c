#include <ush.h>

static void free_env(t_env *env) {
    mx_free_void_arr((void**)env->env_var, mx_count_arr_el(env->env_var));
    mx_strdel(&env->comm_args);
    mx_strdel(&env->comm);
    if (env != NULL) {
        free(env);
        env = NULL;
    }
}

static int check_flag(char **args, int i, t_env *env) {
    if (mx_strcmp(args[i], "--") == 0) {
        env->flag = 4;
        return 0; //continue
    }
    else if (args[i][0] == '-' && env->flag != 4) {
        if (mx_find_flag("Piu", args[i]) == 0) {
            fprintf(stderr, MX_ENV_IL, args[i][1]);
            free_env(env);
            return -1;
        }
        else if (mx_find_flag("Piu", args[i]) < 3 && env->flag == 0 && args[i + 1] == NULL) {
            fprintf(stderr, MX_ENV_US, args[i][1]);
            free_env(env);
            return -1;//break
        }
        else if (mx_find_flag("Piu", args[i]) > env->flag)
            env->flag = mx_find_flag("Piu", args[i]);
        return 0;
    }
    return 1;//nothing
}

static t_env *create_env(void) {
    t_env *env = malloc(sizeof(t_env));
    int i = 0;
    extern char **environ;

    env->flag = 0;
    env->comm = NULL;
    env->env_var = NULL;
    env->comm_args = NULL;
    env->env_var = malloc((mx_count_arr_el(environ) + 1) * sizeof(char *));
    for (int j = 0; environ[j] != NULL; j++)
        env->env_var[i++] = mx_strdup(environ[j]);
    env->env_var[i] = NULL;
    return env;
}

static void create_command(t_env *env, char *arg) {
    int y = 0;

    for (; env->env_var[y]!= NULL; y++) {
        if(strstr(env->env_var[y], "PATH=") != NULL) {
            break;
        }
    }
    if (env->env_var[y] == NULL)
        env->comm = mx_coomand_in_path(arg, MX_PATH());
    else {
        env->comm = mx_coomand_in_path(arg, env->env_var[y]);//поменять место для чистки и путь
    }
}

static int do_command(t_env *env, char **args, int i) {
    int len = 0;

    env->comm_args = mx_strdup(env->comm);
    for (int j = i + 1; args[j] != NULL; j++) {
        len = mx_strlen(env->comm_args) + mx_strlen(args[j]) + 2;
        env->comm_args = realloc(env->comm_args, len);
        mx_strcat(env->comm_args," ");
        mx_strcat(env->comm_args,args[j]);
    }
    return -1;
}

static void flag_P(t_env *env, char *arg) {
    for (int y = 0; env->env_var[y]!= NULL; y++) {
        if(strstr(env->env_var[y], "PATH=") != NULL) {
            mx_strdel(&env->env_var[y]);
            env->env_var[y] = mx_strjoin("PATH=", arg);
            break;
        }
    }
}

static int flag_i(t_env *env, char **args, int i, int *env_index) {
    if (mx_get_char_index(args[i], '=') == 0) {
        fprintf(stderr, "env: setenv %s: Invalid argument\n", args[i]);;
        free_env(env);
        return -1;
    }
    if (args[i-1][0] == '-') {
        mx_free_void_arr((void **) env->env_var, mx_count_arr_el(env->env_var));
        env->env_var = malloc((1) * sizeof(char *));
        env->env_var[*env_index++] = mx_strdup(args[i]);
        env->env_var[*env_index] = NULL;
    }
    else {
        env->env_var = realloc(env->env_var, *env_index + 2);
        env->env_var[*env_index++] = mx_strdup(args[i]);
        env->env_var[*env_index] = NULL;
    }
    return 0;
}

static int flag_u(t_env *env, char *arg) {
    int y = 0;
    char *temp = NULL;
    extern char **environ;

    if (mx_get_char_index(arg, '=') >= 0) {
        fprintf(stderr, "env: unsetenv %s: Invalid argument\n", arg);;
        free_env(env);
        return -1;
    }
    mx_free_void_arr((void**)env->env_var, mx_count_arr_el(env->env_var));
    env->env_var = malloc((1) * sizeof(char*));
    temp = mx_strjoin(arg, "=");
    for (int j = 0; environ[j]!= NULL; j++) {
        if(strstr(environ[j], temp) == NULL) {
            env->env_var = realloc(env->env_var,(y + 2) * sizeof(char*));//больщая трата времени
            env->env_var[y++] = mx_strdup(environ[j]);
        }
    }
    env->env_var[y] = NULL;
    mx_strdel(&temp);
    return 0;
}

static int execute_env_flags(t_env *env, char **args, int i, int *env_index) {
    if (env->comm != NULL && mx_strcmp(args[i],env->comm) != 0)
        return do_command(env, args, i);
    else if (env->flag == 1 && args[i-1][0] == '-' && mx_file_exist(args[i]) == 1)
        flag_P(env, args[i]);
    else if (env->flag == 2 && mx_get_char_index(args[i], '=') >= 0)
        return flag_i(env, args, i, env_index);
    else if (env->flag == 3 && args[i-1][0] == '-')
        return flag_u(env, args[i]);
    else {
        if (mx_file_exist(args[i]) != 1)
            fprintf(stderr, "env: %s: No such file or directory\n", args[i]);
        else if (mx_file_exist(args[i]) == 1)
            fprintf(stderr, "env: %s: Permission denied\n", args[i]);
        free_env(env);
        return -1;
    }
    return 0;
}

static t_env *parse_env_args(char **args) {// 0 - no; 1 - s(priority); 2 - P; 3 - dir or --
    t_env *env = create_env();
    int len = mx_count_arr_el(args);
    int env_index = 0;

    for (int i = 1; i < len; i++) {
        if (check_flag(args, i, env) == -1)
            break;
        else if (check_flag(args, i, env) == 0)
            continue;
        create_command(env, args[i]);
        if (execute_env_flags(env, args, i, &env_index) == -1)
            break;
        mx_strdel(&env->comm);
    }
    return env;
}

int mx_env(char **args, char *ush_path) {
    t_env *env = parse_env_args(args);
    int ret_val = 0;

    if (env != NULL) {
        if (env->comm == NULL || mx_strcmp(env->comm, "env") == 0)
            mx_print_strarr(env->env_var, "\n");
        else if (env->comm != NULL) {
            ret_val = mx_execute(env->comm_args, 0, ush_path);
//            if (fork())
//                wait(NULL);
//            else {
//                //mx_print_strarr(env->comm_args, "\n");
//                if (execve(env->comm_args[0], env->comm_args, env->env_var) == -1)//child execute
//                    perror("execve");
//                exit(1);
//            }
        }
        free_env(env);
    }
    else
        ret_val =  1;
    return ret_val;
}

