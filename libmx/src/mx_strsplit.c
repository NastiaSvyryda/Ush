#include "../inc/libmx.h"

char **mx_strsplit(const char *s, char c){
    int count_words = 0;
    char **arr = NULL;
    int index = 0;
    int j = 0;
    if (s != NULL) {
        count_words = mx_count_words(s, c);
        arr = malloc((count_words + 1) * sizeof(char *));
        for (int i = 0; i < count_words; i++) {
            while (s[index] == c) {
                index++;
            }
            arr[i] = NULL;
            j = 0;
            for( ;s[index] != c && s[index] != '\0'; j++, index++) {
                arr[i] = mx_realloc(arr[i], sizeof(char) * (j + 2));
                arr[i][j] = s[index];
            }
            arr[i][j] = '\0';
        }
        arr[count_words] = NULL;
        return arr;
    }
    return NULL;
}
