#include <ush.h>

void mx_push_execute_queue(t_queue **queue, char *ush_path) {
    int status = 0;

    for(int i = 0; queue[i] != NULL; i++) {
        while(queue[i] != NULL) {
            status = mx_execute(queue[i]->data, 0, ush_path);
            if (status == 0 && queue[i]->operator == '&') {
                mx_pop_front_queue(&queue[i]);
                continue;
            } else if (queue[i]->operator == '|' && status == 0) {
                mx_pop_front_queue(&queue[i]);
                while (queue[i] != NULL && queue[i]->operator == '|'){
                    mx_pop_front_queue(&queue[i]);
                }
                if (queue[i] != NULL)
                    mx_pop_front_queue(&queue[i]);
                continue;
            } else
                mx_pop_front_queue(&queue[i]);
        }
    }
}
