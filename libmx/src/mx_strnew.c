#include "libmx.h"

char *mx_strnew(const int size) {
    char *memory = NULL;
    int i = 0;

    if (size < 0)
        return NULL;
    memory = (char *) malloc((size + 1) * sizeof(char));
    while (i < size) {
        memory[i] = '\0';
        i++;
    }
    memory[i] = '\0';
    return memory;
}
//char *mx_strnew(const int size){
//    char *str = (char*) malloc((size + 1) * sizeof (char));
//    if(str == NULL){
//        return NULL;
//    }
//    for(int i = 0; i < size; i++){
//        str[i] = '\0';
//    }
//    str[size] = '\0';
//    return str;
//}
