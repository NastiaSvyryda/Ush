#include "../inc/libmx.h"

static void delete_arr(char **p , int count_words) {
    if (p == NULL)
        return;
    for (int i = 0; i < count_words; i++) {
        if (p[i] != NULL)
            free(p[i]);
    }
    free(p);
    p = NULL;
}

static bool is_next_word(int *start, int *end, char *s, char c) {
    *start = *end + 1;

    while (s[*start] == c && s[*start]) {
        (*start)++;
    }
    if (s[*start] == '\0')
        return false;

    *end = *start;
    while (s[*end] != c && s[*end]) {
        (*end)++;
    }
    (*end)--;
    return true;
}

char **mx_strsplit(char const *s, char c) {
    if (s == NULL)
        return NULL;

    int count_words = mx_count_words(s, c);
    char **p = (char **) malloc(count_words * sizeof(char *) + 1);
    if (p == NULL)
        return NULL;

    int start = -1;
    int end = -1;
    int i = 0;
    while (is_next_word(&start, &end, (char *)s, c)) {
        char *str = mx_strnew(end - start);
        if (str == NULL)
            delete_arr(p, count_words);
        mx_strncpy(str, &s[start], end - start + 1);
        str[end - start + 1 + 1] = '\0';
        p[i] = str;
        i++;
    }
    p[i] = NULL;
    return p;
}

