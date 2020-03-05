#include <ush.h>

int mx_count_queue_operation(const char *arr) {
    int counter = 0;

    for(int i = 0; arr[i] != '\n'; i++) {
        if(arr[i] == '&' && arr[i + 1] == '&')
            counter++;
        if(arr[i] == '|' && arr[i + 1] == '|')
            counter++;
    }
    return counter;
}
