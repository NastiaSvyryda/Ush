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
    if (input->input_ch_arr[2] == MX_UP_ARROW) { // UP
        mx_printstr(ush->history->head->data);
        //ush->history->data = ush->history->next->data;
    }
    //else if (input->input_ch_arr[2] == MX_DOWN_ARROW) // DOWN
        //mx_printstr(ush->history->data);
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
