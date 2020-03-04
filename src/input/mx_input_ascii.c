#include "ush.h"

static void events (t_input *input) {
    if (input->input_ch == 4) { //^D
        mx_printstr("\n");
        set_canonic(input->savetty);
        exit(0);
    }
    else if (input->input_ch == 3) { //^C
        mx_printstr("\n");
        input->ctrl_c = 1;
    }
}

char *mx_input_ascii(t_input *input) {
    char *ret_str = NULL;
    if (input->input_ch != '\r'  && input->input_ch != '\t' && input->input_ch < 32)
        events(input);
    else {
        ret_str = mx_fill_command(input); //
    }
    return ret_str;
}
