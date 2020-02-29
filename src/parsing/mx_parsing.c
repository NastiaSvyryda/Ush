#include <ush.h>

t_queue *mx_create_queue(void *data, char operation) {
    t_queue *new_node = NULL;

    if (!data)
        return NULL;
    else {
        new_node = (t_queue *)malloc(sizeof(t_queue));
        if (!new_node)
            return NULL;
        new_node->data = data;
        new_node->operator = operation;
        new_node->next = NULL;
        return new_node;
    }
}

void mx_push_back_queue(t_queue **queue, void *data, char operation) {
    t_queue *back_list = mx_create_queue(data, operation);
    t_queue *temp = NULL;
    if (queue == NULL || *queue == NULL)
        *queue = back_list;
    else {
        temp = *queue;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = back_list;
    }
}

int mx_count_queue_operation(char *arr) {
    int counter = 0;

    for(int i = 0; arr[i] != '\n'; i++) {
        if(arr[i] == '&' && arr[i + 1] == '&')
            counter++;
        if(arr[i] == '|' && arr[i + 1] == '|')
            counter++;
    }
    return counter;
}

t_queue *mx_insort_t_queue(char *arr, t_queue *arr_queue) {
    int count = mx_count_queue_operation(arr);
    mx_push_back_queue(&arr_queue, arr, 's');
    mx_printint(count);
    return arr_queue;
}

void mx_parsing(char *command) {
    char **arr = mx_strsplit(command, ';');
    int size = mx_count_arr_el(arr);
    t_queue **arr_queue = (t_queue **)malloc(sizeof(t_queue) * size + 1);

    for (int i = 0; i < size; ++i) {
        mx_insort_t_queue(arr[i], arr_queue[i]);
    }
    arr_queue[size + 1] = NULL;
}
