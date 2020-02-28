#include <ush.h>

static void set_non_canonic(struct termios *savetty) {
    struct termios tty;

    if ( !isatty(0) ) {
        fprintf (stderr, "stdin not terminal\n");
        exit (1);
    }
    tcgetattr (0, &tty);
    *savetty = tty;
    tty.c_lflag   &= ~(ICANON | ECHO | ISIG);
    tty.c_cc[VMIN] = 1;
    tcsetattr (0, TCSAFLUSH, &tty);
}

static void set_canonic(struct termios savetty) {
    tcsetattr (STDIN_FILENO, TCSANOW, &savetty);
}

static char *enable_noncanonic_backspace(char ch, size_t *top, char *str) {
    const char delbuf[] = "\b \b";
    char *ret_str = NULL;
    switch (ch) {
        case 127:
            if (top) {
                --(*top);
                write(STDOUT_FILENO, delbuf, strlen(delbuf));
            }
            break;
        case '\n':
            ret_str = strndup(str, *top);
            break;
        default:
            str[(*top)++] = ch;
            write(STDOUT_FILENO, &ch, sizeof ch);

            break;
    }
    return ret_str;
}

static char *read_str(char *str) {
    char ch = '\0';
    size_t top = 0;
    char *ret_str = NULL;
    int i = 0;

    str = mx_strnew(sizeof (char) * CHAR_MAX/8);
    while (1) {
        read(0, &ch,4);
        if (ch != 0 && ch != 67 && ch != 68)
            ret_str = enable_noncanonic_backspace(ch, &top, str);
        if(ch == KEYCODE_R){
            mx_printint(KEYCODE_R);
        }
        if(ch == KEYCODE_L){
            mx_printint(ch);
        }
        if  (ch == 4) { //^D
            mx_printstr("\n");
            exit(0);
        }
        else if (ch == 3) { //^C
            mx_printstr("\n");
            mx_strdel(&ret_str);
            break;
        }
        else if(ch == '\n') {
            mx_printchar('\n');
            break;
        }
        i++;
    }
    if( ret_str == NULL|| ret_str[0] == '\0' )
        return NULL;
    return ret_str;
}


char *mx_process_input(int *status) {// сделать обработку \ и enter перенос строки продолжение ввода
    // обработка в другом процессе () subshell
    char *str = NULL;
    status++;
    struct termios savetty;

    set_non_canonic(&savetty);
    str = read_str(str);
    set_canonic(savetty);
    return str;
}
