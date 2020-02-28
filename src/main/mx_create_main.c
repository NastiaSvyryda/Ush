#include <ush.h>

t_main* mx_create_main(int argc, char **argv) {
    t_main *main = malloc(sizeof(t_main));

    main->argc = argc;
    main->argv = argv;
    main->command = NULL;
    main->env = NULL;
    main->history = NULL;
    main->emodji_num = 128512;
    main->exit_status = 1;
    return main;
}
