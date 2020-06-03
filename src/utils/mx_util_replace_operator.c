#include <ush.h>

char *mx_util_replace_operator(char *s) {
    s = mx_strtrim(s);
    if (mx_get_substr_index(s," &&")  >= 0)
        s = mx_replace_substr(s, " &&", "&&");
    else if (mx_get_substr_index(s," ||")  >= 0)
        s = mx_replace_substr(s, " ||", "||");
    else if (mx_get_substr_index(s,"&& ")  >= 0)
        s = mx_replace_substr(s, "&& ", "&&");
    else if (mx_get_substr_index(s,"|| ")  >= 0)
        s = mx_replace_substr(s, "|| ", "||");
    return s;
}
