#include "ush.h"

char *mx_input_ascii(t_input *input) {
    char *ret_str = NULL;
    if(input->input_ch >= 32 || input->input_ch == 13) { //&& input->input_ch != MX_ENTER) {
//        //return NULL;
//    }
//    else {
        ret_str = mx_fill_command(input);
    }
    return ret_str;
}
