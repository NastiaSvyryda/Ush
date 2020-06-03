#include <ush.h>

int mx_push_execute_queue(t_queue **queue, t_ush *ush) {
    int status = 0;

    for (int i = 0; queue[i] != NULL; i++) {
        while (queue[i] != NULL) {
            status = mx_execute(ush, queue[i]->data, 0);
            if (ush->exit_status != -1)
                return status;
            if (status == 0 && queue[i]->operator == '&') {
                mx_pop_front_queue(&queue[i]);
                continue;
            }
            else if (queue[i]->operator == '|' && status == 0) {
                mx_pop_front_queue(&queue[i]);
                while (queue[i] != NULL && queue[i]->operator == '|')
                    mx_pop_front_queue(&queue[i]);
                if (queue[i] != NULL)
                    mx_pop_front_queue(&queue[i]);
                continue;
            }
            else
                mx_pop_front_queue(&queue[i]);
        }
    }
    return status;
}