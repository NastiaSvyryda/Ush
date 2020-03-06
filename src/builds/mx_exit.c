#include <ush.h>

void mx_exit(char **input) {
    int exitt = 0;
    if (mx_count_arr_el(input) == 1) {
        exit(0);
    }
    else if (mx_atoi(input[1]) == 0 && mx_count_arr_el(input) == 2) {
        fprintf(stderr, "ush: exit: %s: numeric argument required\n", input[1]);
    }
    else if (mx_count_arr_el(input) == 2) {
        exitt = mx_atoi(input[1]);
        exit(exitt);
    }
    else
        fprintf(stderr, "ush: exit: too many arguments\n");
}
