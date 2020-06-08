#include "ush.h"

static char *previous_dir(void) {
    char *prev_dir = MX_PWD();
    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--) {
        if (prev_dir[i] == '/') {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    return prev_dir;
}

static char *handle_path(char *path, int i, int *flag_recursion) {
    char *value = NULL;
    char *tmp = NULL;
    char *pwd = MX_PWD();

    if (mx_strcmp(path, "-") == 0) {
        if (MX_OLDPWD() != NULL)
            value = mx_strdup(MX_OLDPWD());
        else
            fprintf(stderr, "ush: cd: OLDPWD not set\n");
    }
    else if (mx_count_substr(path, "../") > 0) {
        *flag_recursion = 1;
        setenv("OLDPWD", pwd, 1);
        //mx_printint(mx_count_substr(path, "../"));
        for (int y = 0; y < mx_count_substr(path, "..") - 1; y ++) {
            value = previous_dir();
            if (chdir(value) != -1)
                setenv("PWD", value, 1);
            mx_strdel(&value);
        }
        value = previous_dir();
    }
    else if (path[0] != '.') {
        tmp = mx_strjoin(pwd, "/");
        value = mx_strjoin(tmp, path);
        mx_strdel(&tmp);
    }
    else if (mx_strcmp(path, ".") != 0) {
        value = mx_strdup(pwd);
        value = mx_realloc(value, mx_strlen(value) + mx_strlen(path) + 2);
        for (; i < mx_strlen(path); i++)
            value[mx_strlen(value) + i] = path[i + 1];
        value[mx_strlen(value) + i] = '\0';
    }
    else if (mx_strcmp(path, ".") == 0) {
        value = MX_PWD();
    }
    mx_strdel(&pwd);
    return value;
}

static void cd_print_error(char *arg, char *path) {
    if (mx_strcmp(arg, "-") != 0) {
        if (mx_file_exist(path) == 0)
            fprintf(stderr, "cd: no such file or directory: %s\n", arg);
        else
            fprintf(stderr, "cd: not a directory: %s\n", arg);
    }
}

static char *handle_path_value(char *arg, int *flag_recursion) {
    DIR *dp = NULL;
    char *path = NULL;

    if (arg[0] == '/')
        path = mx_strdup(arg);
    else
        path = handle_path(arg, 0, flag_recursion);
    dp = opendir(path);
    if (dp != NULL) {
        closedir(dp);
        return path;
    }
    else if (dp == NULL)
        cd_print_error(arg,path);
    mx_strdel(&path);
    return NULL;
}

char *mx_parse_cd_args(char **args, int *flag, int len, int *flag_recursion) {
    char *arg = NULL;
    int stop = 0;

    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        arg = MX_HOME();
    else {
        for (int i = 1; i < len; i++) {
            if (mx_strcmp(args[i], "--") == 0) {
                stop = 3;
                continue;
            }
            if (stop == 0 && args[i][0] == '-') {
                if ((*flag = mx_find_flag("Ps", args[i])) > 0)
                    continue;
            }
            arg = handle_path_value(args[i], flag_recursion);
            break;
        }
    }
    return arg;
}


