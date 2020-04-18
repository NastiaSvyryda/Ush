#include "ush.h"

static void right_arrow (t_input *input) {
    if (input->coursor_position < input->len) {
        mx_printstr("\033[C");
        input->coursor_position++;
    }
}

static void left_arrow (t_input *input) {
    if (input->coursor_position > 0) {
        mx_printstr("\033[D");
        input->coursor_position--;
    }

}

void mx_input_non_ascii(t_input *input) {
    if (input->input_ch == 27) {
        if (input->input_ch_arr[1] == 91) {
            if (input->input_ch_arr[2] == MX_RIGHT_ARROW)
                right_arrow(input);
            if (input->input_ch_arr[2] == MX_LEFT_ARROW)
                left_arrow(input);
        }
    }
}
