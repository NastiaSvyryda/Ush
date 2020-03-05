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

#define KEYCODE_R 67
#define KEYCODE_L 68
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42

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
};

struct s_ush {
    int argc;
    char **argv;
    char *command;
    t_env *env;
    t_list *history;
    wchar_t emodji_num;
    int exit_status;
};

//Main function
t_ush* mx_create_ush(int argc, char **argv);
int main(int argc, char **argv);
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
char *mx_process_input(int *status, t_ush *ush);
//Parsing function
void mx_parsing(char *command);
t_queue *mx_create_queue(void *data, char operation);
void mx_push_back_queue(t_queue **queue, void *data, char operation);
int mx_count_queue_operation(char *arr);
t_queue *mx_insort_t_queue(char *arr, t_queue *arr_queue);
//Printing function
void mx_print_prompt(wchar_t *emodji_num);
//Validations function
#endif
