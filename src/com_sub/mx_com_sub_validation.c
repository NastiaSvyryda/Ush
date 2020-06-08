#include "ush.h"

void mx_com_sub_validation(char **data, t_ush *ush) {
    t_com_sub *com_sub = mx_create_com_sub();

    char *temp_str = NULL;
    char *temp_data = NULL;
    char *cout_execute = NULL;
    char *temp_join = NULL;

    int status = 0;
    int exit = 0;

    for (int i = 0; (*data)[i] != '\0'; i++) {
        if ((*data)[i] == '`') {
            if (com_sub->space == 0) {
                com_sub->space++;
                com_sub->space_first_index = i;
            }
            else if (com_sub->space == 1) {
                com_sub->space++;
                com_sub->space_end_index = i;
            }
            if (com_sub->space_first_index < com_sub->space_end_index) {
                exit = 1;
                temp_str = mx_util_strindup(*data, com_sub->space_first_index + 1, com_sub->space_end_index);
                status = mx_execute(ush, temp_str, 1, &cout_execute);
                temp_join = mx_strjoin("`", temp_str);
                mx_strdel(&temp_str);
                temp_str = mx_strjoin(temp_join, "`");
                if (status == 0)
                    temp_data = mx_replace_substr(*data, temp_str, cout_execute);
                else
                    temp_data = mx_replace_substr(*data, temp_str, "");
                mx_strdel(&temp_join);
                mx_strdel(&temp_str);
                mx_strdel(&cout_execute);
                if (temp_data != NULL) {
                    mx_strdel(data);
                    *data = temp_data;
                    break;
                }
            }
        }
        if ((*data)[i] == '$' && (*data)[i + 1] == '(') {
            if (com_sub->back_first == 0) {
                com_sub->back_first++;
                com_sub->back_first_index = i;
            }
        }
        if (com_sub->back_first == 1 && (*data)[i] == ')') {
            com_sub->back_end++;
            com_sub->back_end_index = i;
        }
        if (com_sub->back_first_index < com_sub->back_end_index) {
            exit = 1;
            temp_str = mx_util_strindup(*data, com_sub->back_first_index + 2, com_sub->back_end_index);
            status = mx_execute(ush, temp_str, 1, &cout_execute);
            temp_join = mx_strjoin("$(", temp_str);
            mx_strdel(&temp_str);
            temp_str = mx_strjoin(temp_join, ")");
            if (status == 0)
                temp_data = mx_replace_substr(*data, temp_str, cout_execute);
            else
                temp_data = mx_replace_substr(*data, temp_str, "");
            mx_strdel(&temp_join);
            mx_strdel(&temp_str);
            mx_strdel(&cout_execute);
            if (temp_data != NULL) {
                mx_strdel(data);
                *data = temp_data;
                break;
            }
        }
    }
    free(com_sub);
    if (exit == 1)
        mx_com_sub_validation(data, ush);
}
