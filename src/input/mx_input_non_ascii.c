#include "ush.h"

static void key_right_left(t_input *input) {
    if (input->input_ch_arr[2] == 67 && input->i > 0) { // RIGHT
        input->left--;
        input->i--;
        mx_printstr("\033[C");
    }
    else if (input->input_ch_arr[2] == 68 && input->i < input->len - 1) { // LEFT
        input->i++;
        input->left++;
        mx_printstr("\033[D");
    }
}
static void key_up_down(t_input *input, t_ush *ush) {
    if (input->input_ch_arr[2] == 65) { // UP
        mx_printstr(ush->history->next->data);
    }
    else if (input->input_ch_arr[2] == 66) { // DOWN
        mx_printstr(ush->history->data);
    }
}


void mx_input_non_ascii(t_input *input, t_ush *ush) {
    if (input->input_ch_arr[0] == 27) {
        if ((input->input_ch_arr[2] == 67
            || input->input_ch_arr[2] == 68)
            && input->len > 0) {
            key_right_left(input);
        }
        else if (input->input_ch_arr[2] == 65 || input->input_ch_arr[2] == 66)
            key_up_down(input, ush);
    }
}
