#include "ush.h"

static void setenv_ush(char **args, char *arg, int flag_recursion) {
    char *pwd = MX_PWD();
    char *tmp = NULL;
    char *tmmp = NULL;

    if (flag_recursion == 0)
        setenv("OLDPWD", pwd, 1);
    if (mx_strlen(arg) != 1 && arg[mx_strlen(arg) - 1] == '/')
        arg[mx_strlen(arg) - 1] = '\0';
    setenv("PWD", arg, 1);
    if (mx_strcmp(args[1], "-") == 0) {
        tmmp = MX_HOME();
        tmp = mx_replace_substr(arg, tmmp, "~");
        if (tmp != NULL)
            printf("%s\n", tmp);
        else
            printf("%s\n", arg);
        mx_strdel(&tmmp);
        mx_strdel(&tmp);
    }
    mx_strdel(&pwd);
}

int mx_cd(char **args) {
    int flag = 0;
    int fl_rec = 0;
    char *arg = mx_parse_cd_args(args, &flag, mx_count_arr_el(args), &fl_rec);
    int return_ = 0;

    if (arg != NULL) {
        if (flag == 2 && mx_check_symlink(arg, flag, 1) == 1) {
            fprintf(stderr, "cd: not a directory: %s\n", arg);
            return_ = 1;
        }
        else if (chdir(arg) != -1)
            setenv_ush(args, arg, fl_rec);
        else
            printf("%s\n", arg);
        mx_strdel(&arg);
        return return_;
    }
    return 1;
}
