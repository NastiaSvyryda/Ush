#include "../inc/libmx.h"

void mx_swaps_arr(char **arr, int i, int j) {
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
