#include <ush.h>

int mx_cd(char **args) {
    int flag = 0;
    char *arg = mx_parse_cd_args(args, &flag, mx_count_arr_el(args));
    int return_ = 0;

    if (arg != NULL) {
        if (flag == 2 && mx_check_symlink(arg, flag, 1) == 1) {
            fprintf(stderr, "cd: not a directory: %s\n", arg);
            return_ = 1;
        }
        else if (chdir(arg) != -1) {
            setenv("OLDPWD", MX_PWD(), 1);
            setenv("PWD", arg, 1);
            if(mx_strcmp(args[1], "-") == 0)
                printf("%s\n", arg);
        }
        else
            printf("%s\n",arg);
        mx_strdel(&arg);
    }
    else
        return_ = 1;
    return  return_;
}
