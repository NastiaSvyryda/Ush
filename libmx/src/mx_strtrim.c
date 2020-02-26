#include "../inc/libmx.h"

char *mx_strtrim(const char *str){
    int end = 0;
    int start = 0; 
    int a = 0;
    char *new_str = malloc(sizeof(char));
    int j = 0;

    if (str != NULL){
        end = mx_strlen(str);
        while(mx_isspace(str[a])){
            start++;
            a++;
        }
        while(mx_isspace(str[end-1])){
            end--;
        }
        new_str = mx_realloc(new_str,end - start + 1);
        for(int i = start; i < end; i++){
            new_str[j++] = str[i];
        }
        new_str[end - start] = '\0';
        return new_str;
    }
    mx_strdel(&new_str);
    return NULL;
}
     

          

