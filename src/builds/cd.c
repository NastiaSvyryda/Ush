#include "ush.h"

static char *previous_dir(void) {
    char *prev_dir = mx_strdup(MX_PWD());
    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--) {
        if (prev_dir[i] == '/') {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    return prev_dir;
}
static char *handle_path(char *path) {
    char *value = NULL;
    int i = 0;
    if (path[0] == '/')
        value = mx_strdup(path);
    else {
        value = mx_strdup(MX_PWD());
        value = mx_realloc(value, mx_strlen(value) + mx_strlen(path) + 2);
        if (mx_strcmp(path, "..") == 0 || mx_strcmp(path, "-") == 0)//redo -
            value = previous_dir();
        else if (path[0] != '.') {
            mx_strcat(value, "/");
            mx_strcat(value, path);
        }
        else if (mx_strcmp(path, ".") != 0) {
            for (; i < mx_strlen(path); i++)
                value[mx_strlen(value) + i] = path[i + 1];
            value[mx_strlen(value) + i] = '\0';
        }
    }
    return value;
}
static int check_symlink(char *arg, int flag) {
    struct stat *st = (struct stat*) malloc(sizeof (struct stat));
    int is_link = 0;
    char buf[1024];
    ssize_t len = 0;
    char *path = arg;
    lstat(arg, st);
    //perror("lstat");
    if ((st->st_mode & S_IFMT) == S_IFLNK) {
        is_link = 1;
        if (flag == 2) {
            //path = handle_path(arg);
            if ((len = readlink(path, buf, 1024)) == -1)
                perror("readlink");
            buf[len] = '\0';
            mx_strdel(&arg);
            arg = mx_strnew(mx_strlen(buf) + 1);
            arg[0] = '/';
            mx_strcat(arg, buf);
            //mx_strdel(&path);
        }
    }
    free(st);
    st = NULL;
    return is_link;
}
static int file_exist(char *path) {
    struct stat *st = (struct stat*) malloc(sizeof (struct stat));
    int flag = 0;
    if ((lstat(path, st) != -1))
        flag = 1;
    free(st);
    st = NULL;
    return flag;
}
static void cd_print_error(char **args, int i, char *path, int len) {
    if (args[i + 2] != NULL && len > 3)
        fprintf(stderr, "cd: too many arguments\n");
    else if (args[i + 1] != NULL)
        fprintf(stderr, "cd: string not in pwd: %s\n", args[i]);
    else if (file_exist(path) == 0)//-s links
        fprintf(stderr, "cd: no such file or directory: %s\n", args[i]);
    else
        fprintf(stderr, "cd: not a directory: %s\n", args[i]);
    mx_strdel(&path);
}
static char *parse_cd_args(char **args, int *flag) {// 0 - no; 1 - s(priority); 2 - P; 3 - dir or --
    char *arg = NULL;
    DIR *dp = NULL;
    char *path = NULL;
    int len = mx_count_arr_el(args);
    int stop = 0;
    if (len == 1 || (mx_strcmp(args[1], "--") == 0 && len == 2))
        arg = mx_strdup(MX_HOME());
    for (int i = 1; i < len; i++) {
        if (stop == 0 && (mx_strcmp(args[i], "--") == 0 || mx_strcmp(args[i], "-s") == 0 || mx_strcmp(args[i], "-P") == 0)) {
            if (mx_strcmp(args[i], "--") == 0)
                stop = 1;
            else if (mx_strcmp(args[i], "-s") == 0)
                *flag = 1;
            else if (mx_strcmp(args[i], "-P") == 0 && *flag != 1)
                *flag = 2;
            continue;
        }
        path = handle_path(args[i]);
        dp = opendir(path);
        if (dp != NULL && args[i + 1] == NULL) {// . .. - --
            if (dp != NULL)
                closedir(dp);
            arg = mx_strdup(path);
            stop = 1;
        }
        else if (dp == NULL || args[i + 1] != NULL) {
            if (dp != NULL)
                closedir(dp);
            cd_print_error(args, i, path, len);
            break;
        }
        mx_strdel(&path);
    }
    return arg;
}
//static char *real_symlink(char *arg) {
//
//}
void cd(char **args) {
    int flag = 0;
    char *arg = parse_cd_args(args, &flag);
    int is_link = 0;
    if (arg != NULL) {
        is_link = check_symlink(arg, flag);
        if (flag == 1 && is_link == 1)
            fprintf(stderr, "cd: not a directory: %s\n", arg);
        else if (chdir(arg) != -1) {
            setenv("PWD", arg, 1);
        } else
            printf("%s\n",arg);
        mx_strdel(&arg);
    }
}
