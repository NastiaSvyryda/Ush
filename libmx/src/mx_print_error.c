#include "../inc/libmx.h"

void mx_print_error(char *str) {
    write(2, str, mx_strlen(str));
}
