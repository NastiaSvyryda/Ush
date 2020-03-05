#include <ush.h>

int mx_export(char **args) {
    char *name = NULL;
    char *value = NULL;
    int len_n = 0;
    int len_v = 0;
    //char *tmp = MX_CUR_EXEC();

    //unsetenv("_");
    for (int y = 1; y < mx_count_arr_el(args); y++) {
        len_n = mx_get_char_index(args[y], '=');
        if (len_n != -1) {
            len_v = mx_strlen(args[y]) - len_n - 1;
            name = mx_strnew(len_n);
            value = mx_strnew(len_v);
            for (int i = 0; args[y][i] != '='; i++) {
                name[i] = args[y][i];
            }
            for (int i = 0; args[y][len_n + i + 1] != '\0'; i++) {
                value[i] = args[y][len_n + i + 1];
            }
            setenv(name, value, 1);
            mx_strdel(&name);
            mx_strdel(&value);
        }
        return 1;
    }
    //setenv("_", tmp, 1);
    return 0;
}

int mx_unset(char **args) {
    for (int y = 1; y < mx_count_arr_el(args); y++) {
        unsetenv(args[y]);
    }
    return 0;
}


