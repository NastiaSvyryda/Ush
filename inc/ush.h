#ifndef USH_H
#define USH_H

#include "libmx.h"
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>


#define MX_TMPDIR() (getenv("TMPDIR"))
#define MX_XPC_FLAGS() (getenv("XPC_FLAGS"))
#define MX_APPLE_PUBSUB() (getenv("Apple_PubSub_Socket_Render"))
#define MX_TERM() (getenv("TERM"))
#define MX_SSH_AUTH_SOCK() (getenv("SSH_AUTH_SOCK"))
#define MX_SECURITYSESSIONID() (getenv("SECURITYSESSIONID"))
#define MX_XPC_SERVICE_NAME() (getenv("XPC_SERVICE_NAME"))
#define MX_TERM_PROGRAM() (getenv("TERM_PROGRAM"))
#define MX_TERM_PROGRAM_VERSION() (getenv("TERM_PROGRAM_VERSION"))
#define MX_LC_CTYPE() (getenv("LC_CTYPE"))
#define MX_TERM_SESSION_ID() (getenv("TERM_SESSION_ID"))
#define MX_SHELL() (getenv("SHELL"))
#define MX_HOME() (getenv("HOME"))
#define MX_LOGNAME() (getenv("LOGNAME"))
#define MX_USER() (getenv("USER"))
#define MX_PATH() (getenv("PATH"))
#define MX_SHLVL() (getenv("SHLVL"))
#define MX_PWD() (getenv("PWD"))
#define MX_OLDPWD() (getenv("OLDPWD"))
#define MX_HOMEBREW_CACHE() (getenv("HOMEBREW_CACHE"))
#define MX_HOMEBREW_TEMP() (getenv("HOMEBREW_TEMP"))
#define MX_CUR_EXEC() (getenv("_"))

#define MX_RIGHT_ARROW 67
#define MX_LEFT_ARROW 68
#define MX_UP_ARROW 65
#define MX_DOWN_ARROW 66

#define MX_ENV_US "env: option requires an argument -- %c\nusage: env [-i] [-P utilpath] [-u name]\n"
#define MX_PWD_ERR "ush: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n"

//Enum
typedef enum e_error {
    ERR_EACCES,
    ERR_DIR,
}            t_error;
//Struct
typedef struct s_queue t_queue;
typedef struct s_env t_env;
typedef struct s_process t_process;
typedef struct s_input t_input;
typedef struct s_ush t_ush;

struct s_queue {
    char *data;
    char operator;
    struct s_queue *next;
};
struct s_env {
    char *key;
    char *value;
    struct s_env *next;
};

struct s_process {
    char **name;
    pid_t pid;
    int index;
};

struct s_input {
    int num_backspace;
    int ctrl_c;
    int enter;
    unsigned char input_ch;
    char *input_ch_arr;
    int len;
    int left;
    int coursor_position;
    char *command;
    char *ret_str;
    struct termios savetty;
};

typedef struct s_dbl_node {
    struct s_dbl_node *next;
    struct s_dbl_node *prev;
}              t_dbl_node;

typedef struct s_dbl_list {
    t_dbl_node * first;
    t_dbl_node * last;
    size_t size;
}      t_dbl_list;

typedef struct s_dbl_data {
    t_dbl_node lnk;
    char* data;
}              t_dbl_data;

struct s_ush {
    int argc;
    char **argv;
    char *command;
    t_env *env;
    t_dbl_list *history;
    t_dbl_node *curr_history;
    t_dbl_node *tail_history;
    wchar_t emodji_num;
    int exit_status;
};

//Main function
t_ush* mx_create_ush(int argc, char **argv);
//Builds function
void mx_pwd(char **args);
void mx_cd(char **input);
void mx_env(char **args);
int mx_find_flag(char *flags, char *arg);
int mx_file_exist(char *path);
int check_symlink(char *arg, int flag, int link);
void mx_export(char **args);
void mx_unset(char **args);
void mx_exit(char **input);
//Input function
void mx_clear_str();
void mx_delete_char(t_input *input, int index);
void mx_insert_char(t_input *input, char sym, int index);
char *mx_moving_coursor_str(int num_of_moves);
char *mx_fill_command(t_input *input);
char *mx_process_input(t_ush *ush);
char *mx_input_ascii(t_input *input);
void mx_set_non_canonic(struct termios *savetty);
void set_canonic(struct termios savetty);
void mx_input_non_ascii(t_input *input, t_ush *ush);
//Parsing function
t_queue **mx_parsing(char *command);
int mx_count_queue_operation(const char *arr);
t_queue *mx_create_queue(char *data, char operation);
void mx_push_back_queue(t_queue **queue, char *data, char operation);
t_queue *mx_insort_t_queue(char *arr, t_queue **arr_queue);
//Printing function
void mx_print_prompt(wchar_t emodji_num);
//Validations function
#endif
