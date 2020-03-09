#include <ush.h>

int mx_is_builtin(char *command) {
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
