#include "../inc/ush.h"

static char *cd(char *arr) {
    char *path = mx_strnew(100);

    chdir(arr);
    getwd(path);
    return path;
}

static void foo(char *str) {
    char **arr = mx_strsplit(str, ' ');
    char *path = NULL;

    if (strcmp(arr[0], "cd") == 0)
        path = cd(arr[1]);
    if (strcmp(arr[0], "pwd") == 0)
        printf("%s\n", path);
}

int main() {
    char *str = mx_strnew(sizeof (char) * CHAR_MAX/8);
    int i = 0;
    int len = 0;
    while(i < 2) {
        printf("u$h> ");
        fgets(str, CHAR_MAX/8, stdin);
        len = mx_strlen(str);
        str[len-1] = '\0';
        foo(str);
        i++;

    }
    return 0;
}
