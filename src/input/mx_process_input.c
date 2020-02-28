#include <ush.h>

static void set_non_canonic(struct termios *savetty) {
    struct termios tty;

    if ( !isatty(0) ) {
        fprintf (stderr, "stdin not terminal\n");
        exit (1);
    }
    tcgetattr (0, &tty);
    *savetty = tty;
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
        | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_cflag &= ~(CSIZE | PARENB);
    tty.c_cflag |= CS8;
    tty.c_iflag &= IGNCR;
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);
}

static void set_canonic(struct termios savetty) {
    tcsetattr (STDIN_FILENO, TCSANOW, &savetty);
}

static char *enable_noncanonic_backspace(t_event *event, char *str) {
    const char delbuf[] = "\b \b";
    char *ret_str = NULL;
    switch (event->input_ch) {
        case 127:
            if (event->num_backspace) {
                --event->num_backspace;
                write(STDOUT_FILENO, delbuf, strlen(delbuf));
            }
            break;
        case '\r':
            ret_str = strndup(str, event->num_backspace);
            event->enter = 1;
            mx_printstr("\n");
            break;
        default:
            str[event->num_backspace++] = event->input_ch;
            write(STDOUT_FILENO, &event->input_ch, sizeof event->input_ch);

            break;
    }
    return ret_str;
}
static void events (t_event *event) {
//    if (event->input_ch == 10) {
//        mx_printstr("\n");
//        event->enter = 1;
//    }
    if (event->input_ch == 4) { //^D
        mx_printstr("\n");
        exit(0);
    }
    else if (event->input_ch == 3) { //^C
        mx_printstr("\n");
        event->ctrl_c = 1;
    }

}

static char *input_ascii(t_event *event, char *str) {
    char *ret_str = NULL;
    if (event->input_ch != '\r' && event->input_ch < 32) {
        events(event);
    }
    else {
        ret_str = enable_noncanonic_backspace(event, str);
    }
    return ret_str;
}
//static void key_events (t_event *event) {
//    if (event->input_ch_arr[1])
//}
//static void input_non_ascii(t_event *event) {
//    if (event->input_ch_arr[0] == 27)
//        key_events(event);
//}

static char *read_str(char *str) {
    t_event *event = (t_event *) malloc(sizeof (t_event));
    event->num_backspace = 0;
    char *ret_str = NULL;

    event->input_ch_arr = &event->input_ch;
    str = mx_strnew(sizeof (char) * CHAR_MAX/8);
    while (1) {
        read(0, &event->input_ch, 4);
        if (event->input_ch <= 127)
            ret_str = input_ascii(event, str);
//        else
//            input_non_ascii(event);
//        if(event->input_ch == KEYCODE_R){
//            mx_printint(KEYCODE_R);
//        }
//        if(event->input_ch == KEYCODE_L){
//            mx_printint(event->input_ch);
//        }

        if(event->enter == 1 || event->ctrl_c == 1) {
            break;
        }
    }
    mx_strdel(&str);
    if( ret_str == NULL|| ret_str[0] == '\0' )
        return NULL;
    return ret_str;
}


char *mx_process_input(int *status, t_main *main) {// сделать обработку \ и enter перенос строки продолжение ввода
    // обработка в другом процессе () subshell
    char *str = NULL;
    status++;
    struct termios savetty;

    set_non_canonic(&savetty);
    str = read_str(str);
    mx_push_back(&main->history, str);
    set_canonic(savetty);

    return str;
}
