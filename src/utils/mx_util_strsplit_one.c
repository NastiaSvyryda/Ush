#include <ush.h>

static char *replace(const char *s, char *str_join) {
    int leng_s = mx_strlen(s);
    int leng_str_join = mx_strlen(str_join);
    char *name = NULL;
    int i = 0;
    int j = leng_str_join;

    name = mx_strnew(leng_s - leng_str_join);
    while (s[j]) {
        name[i] = s[j];
        i++;
        j++;
    }
    name[i] = '\0';
    return name;
}

char **mx_util_strsplit_one(const char *s, char *c) {
    char **result = (char**) malloc(sizeof(char*) * (2));
    char *str_join = NULL;
    s  = mx_util_replace_operator((char *)s);
    if(mx_count_queue_operation(s) == 0){
        result[0] = mx_strdup(s);
        result[1] = NULL;
        return result;
    }
    else {
        result[0] = mx_strtrim(mx_strndup(s, mx_get_substr_index(s, c)));
        int and = mx_util_get_flag_index(s, "&&");
        int or = mx_util_get_flag_index(s, "||");
        if ((and >= 0) && (and < or))
            str_join = mx_strjoin(result[0], "&&");
        else
            str_join = mx_strjoin(result[0], "||");
        result[1] = replace(s, str_join);
        return result;
    }
}
