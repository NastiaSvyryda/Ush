#include <ush.h>

t_ush* mx_create_ush(int argc, char **argv) {
    t_ush *ush = malloc(sizeof(t_ush));

    ush->argc = argc;
    ush->argv = argv;
    ush->command = NULL;
    ush->history = NULL;
    ush->emodji_num = 128512;
    ush->exit_status = 1;
    return ush;
}
