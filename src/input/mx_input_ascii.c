#include "ush.h"

static void events (t_input *input, int *exit_status) {
    if (input->input_ch == 4) { //^D
        mx_printstr("\n");
        set_canonic(input->savetty);
        *exit_status = 0;
    }
    else if (input->input_ch == 3) //^C
        input->ctrl_c = 1;
}

char *mx_input_ascii(t_input *input, int *exit_status) {
    char *ret_str = NULL;
    if (input->input_ch != '\r'  && input->input_ch != '\t' && input->input_ch < 32)
        events(input, exit_status);
    else {
        ret_str = mx_fill_command(input); //
    }
    return ret_str;
}
