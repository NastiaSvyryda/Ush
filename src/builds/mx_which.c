#include "ush.h"

static int is_comm_rw(char *str) {
    char reserved_words[][5] = {"!", "{", "}", "time"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(str, reserved_words[i]) == 0)
            return 1;
    }
    return -1;
}

int mx_which(char **input) {
    char **path = NULL;
    int flag = 0;
    int len = mx_count_arr_el(input);
    char *tmp = NULL;
    int ret_flag = 0;

    if (len == 1) {
        fprintf(stderr, "usage: which [-as] program ...\n");
        return 1;
    }
    for (int i = 1; i < len; i++) {
        if (strcmp(input[i], "--") == 0)
            flag = 3;
        else if (input[i][0] == '-' && flag < 3) {
            for (int y = 1; y < mx_strlen(input[i]); y++) {
                if (input[i][y] == 's' && flag != 2) {
                    flag = 1;
                }
                else if (input[i][y] == 'a') {
                    flag = 2;
                }
                else {
                    fprintf(stderr, MX_WHICH_US, input[i][y]);
                    return 1;
                }
            }
            continue;
        }
        if (is_comm_rw(input[i]) == 1)
            printf("%s: shell reserved word\n", input[i]);
        else if (mx_get_char_index(input[i], '/') != -1) {
            path = mx_strsplit(MX_PATH(), ':');
            for (int y = 0; y < mx_count_arr_el(path); y++) {
                if (mx_get_substr_index(input[i], path[y]) != -1
                    && mx_file_exist(input[i])) {
                    if (flag != 1)
                        printf("%s\n", input[i]);
                    ret_flag = 0;
                    break;
                }
                ret_flag = 1;
            }
            mx_free_void_arr((void**)path, mx_count_arr_el(path));
        }
        else {
            tmp = mx_coomand_in_path(input[i], MX_PATH());
            if (mx_is_builtin(tmp) != 0) {
                if (flag != 1)
                    printf("%s: shell built-in command\n", input[i]);
                if (flag == 2 && flag != 1 && strcmp(tmp, input[i]) != 0)
                    printf("%s\n", tmp);
            }
            else if (strcmp(tmp, input[i]) != 0) {
                if (flag != 1)
                    printf("%s\n", tmp);
            }
            else
                ret_flag = 1;
            mx_strdel(&tmp);
        }
    }
    return ret_flag;
}


