#include <ush.h>

static char **mx_strsplit_one(const char *s, char *c) {
    char **result = (char**) malloc(sizeof(char*) * (2));
    char *str_join = NULL;

    if(mx_count_queue_operation(s) == 0){
        result[0] = mx_strdup(s);
        result[1] = NULL;
        return result;
    }
    else {
        result[0] = mx_strtrim(mx_strndup(s, mx_get_substr_index(s, c)));
        if (mx_get_substr_index(s, "&&") >= 0)
            str_join = mx_strjoin(result[0], " &&");
        else
            str_join = mx_strjoin(result[0], " ||");
        result[1] = mx_strtrim(mx_replace_substr(s, str_join, ""));
        return result;
    }
}

t_queue *mx_insort_t_queue(char *arr, t_queue **arr_queue) {
    int count = mx_count_queue_operation(arr);
    int i = 0;
    char **arr_str = NULL;
    char *temp = NULL;

    for(int j = 0; j <= count; j++) {
        if (i == 0 ) {
            i++;
            if (mx_get_substr_index(arr, "&&") >= 0) {
                arr_str = mx_strsplit_one(arr, "&&");
                mx_push_back_queue(arr_queue, arr_str[0], '&');
                temp = arr_str[1];
                continue;
            } else if (mx_get_substr_index(arr, "||") >= 0) {
                arr_str = mx_strsplit_one(arr, "||");
                mx_push_back_queue(arr_queue, arr_str[0], '|');
                temp = arr_str[1];
                continue;
            } else
                mx_push_back_queue(arr_queue, temp, '0');
        } else {
            if (mx_get_substr_index(temp, "&&") >= 0) {
                arr_str = mx_strsplit_one(temp, "&&");
                mx_push_back_queue(arr_queue, arr_str[0], '&');
                temp = arr_str[1];
                continue;
            } else if (mx_get_substr_index(temp, "||") >= 0) {
                arr_str = mx_strsplit_one(temp, "||");
                mx_push_back_queue(arr_queue, arr_str[0], '|');
                temp = arr_str[1];
                continue;
            } else
                mx_push_back_queue(arr_queue, temp, '0');
        }
    }
    return *arr_queue;
}
