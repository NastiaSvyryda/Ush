#include "ush.h"

static void key_right_left(t_input *input) {
    if (input->input_ch_arr[2] == MX_RIGHT_ARROW && input->left > 0) { // RIGHT
        input->left--;

        input->coursor_position++;
        mx_printstr("\033[C");
    }
    else if (input->input_ch_arr[2] == MX_LEFT_ARROW && input->left < input->len - 1) { // LEFT
        input->left++;
        input->coursor_position--;
        mx_printstr("\033[D");

    }
}

static void key_up_down(t_input *input, t_ush *ush) {
    ;
    if (input->input_ch_arr[2] == MX_UP_ARROW) { // UP
//        ush->curr_history = ush->history->first;
        if (ush->history->size > 0) {
            input->command = mx_strdup(((t_dbl_data *) ush->curr_history)->data);
            if(ush->curr_history->next != NULL) {
                ush->curr_history = ush->curr_history->next;
                input->arrow_press++;
            }
        }
    }
    else if (input->input_ch_arr[2] == MX_DOWN_ARROW) { // DOWN
        if (input->arrow_press > 0) {
            input->arrow_press--;
            input->command = mx_strdup(((t_dbl_data *) ush->curr_history->prev)->data);
            if (ush->curr_history->prev != NULL)
                ush->curr_history = ush->curr_history->prev;
        }
    }
    mx_clear_str();
    mx_printstr(input->command);
    input->num_backspace = input->coursor_position = input->len = mx_strlen(input->command);
}


void mx_input_non_ascii(t_input *input, t_ush *ush) {
    if (input->input_ch_arr[0] == 27) {
        if ((input->input_ch_arr[2] == MX_RIGHT_ARROW
            || input->input_ch_arr[2] == MX_LEFT_ARROW)
            && input->len > 0) {
            key_right_left(input);
        }
        else if (input->input_ch_arr[2] == MX_UP_ARROW
                || input->input_ch_arr[2] == MX_DOWN_ARROW) {
            key_up_down(input, ush);
        }
    }
}
