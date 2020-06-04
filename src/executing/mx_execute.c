#include "ush.h"

void sigHandler(int signum){
    int status = 0;
    switch(signum){
        case SIGCHLD:
            // note that the last argument is important for the wait to work
            waitpid(-1, &status, WNOHANG);
            break;
    }
}

void sigtstp(int signum) {
    kill(signum, SIGTSTP);
    printf("\nush: suspended\n");
}
static void par_execute(int *ret_val, int *fd, char **input, int *exit_status) {
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    int command = mx_is_builtin(command_p);
    char *ret_str = mx_strnew(1);
    int status = 0;

    if (command == 1)
        *ret_val = mx_cd(input);
    else if (command == 5)
        *ret_val = mx_export(input);
    else if (command == 6)
        *ret_val = mx_unset(input);
    else if (command == 7)
        *ret_val = mx_exit(input, exit_status);
    waitpid(-1, &status, WUNTRACED);
    mx_read_from_pipe(ret_str, 1, fd);
    if (mx_atoi(ret_str) == 1 || *ret_val == 1)
        *ret_val = 1;
    else
        *ret_val = 0;
    mx_strdel(&ret_str);
    mx_strdel(&command_p);
}

static void child_not_builtin(int *ret_val, char **input, char *command_p) {
    DIR *dp = NULL;
    extern char **environ;

    if ((dp = opendir(command_p)) != NULL) {
        fprintf(stderr, "ush: %s: is a directory\n", input[0]);
        *ret_val = 1;
        closedir(dp);
    }
    else if (mx_file_exist(command_p)) {
        int exec = execve(command_p, input, environ);
        if (exec == -1 && errno == EACCES) {
            fprintf(stderr, "ush: Permission denied:%s\n", input[0]);
            *ret_val = 1;
        }
    }
    else {
        fprintf(stderr, "ush: %s: command not found\n", input[0]);
        *ret_val = 1;
    }
}

static void child_execute(int *ret_val, char **input, int *fd, t_ush *ush) {//убрать return_pipe
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    int command = mx_is_builtin(command_p);
    char *ret = NULL;

    if (command == 2)
        *ret_val = mx_pwd(input);
    else if (command == 3)
        *ret_val = mx_env(input, ush);
    else if (command == 4)
        *ret_val = mx_ush(input, ush->ush_path);
    else if (command == 8)
        *ret_val = mx_which(input);
    else if (command == 9)
        *ret_val = mx_echo(input);
    else if (command == 0)
        child_not_builtin(ret_val, input, command_p);
    ret = mx_itoa(*ret_val);
    mx_write_to_pipe(ret, fd);
    mx_strdel(&ret);
    mx_strdel(&command_p);
    exit(0);
}

static t_redirect *create_redirect(void) {
    t_redirect *redirect = (t_redirect *)malloc(sizeof(t_redirect));
    redirect->_stderr = mx_strnew(1000);
    redirect->_stdout = mx_strnew(1000);
    pipe(redirect->fd_return);
    pipe(redirect->fd_stdout);
    pipe(redirect->fd_stderr);
    return redirect;
}

static void parent_redirect(int flag_redirect, t_redirect *redirect, int *return_) {
    if (flag_redirect == 1)
        mx_read_from_pipe(redirect->_stdout, 1000, redirect->fd_stdout);
    mx_read_from_pipe(redirect->_stderr, 1000, redirect->fd_stderr);
    if (mx_strlen(redirect->_stderr) != 0) {
        *return_ = 1;
        mx_printstr(redirect->_stderr);
    }
}

static void child_redirect(int flag_redirect, t_redirect *redirect) {
    if (flag_redirect == 1) {
        if (dup2(redirect->fd_stdout[1], 1) == -1)
            perror("dup2");
        close(redirect->fd_stdout[0]);
    }
    if (dup2(redirect->fd_stderr[1], 2) == -1)
        perror("dup2");
    close(redirect->fd_stderr[1]);
}

int mx_execute(t_ush *ush, char *str_input, int flag_redirect) {//добавить env для env?
    pid_t pid;
    int return_ = 0;
    char **input = mx_check_expansion(str_input, ush->return_value);
    t_redirect *redirect = create_redirect();

//    signal(SIGTSTP, SIG_IGN);
    pid = fork();
    if (pid != 0) {
        par_execute(&return_, redirect->fd_return, input, &ush->exit_status);
        parent_redirect(flag_redirect, redirect, &return_);
    }
    else {
        signal(SIGTSTP, SIG_DFL);
        child_redirect(flag_redirect, redirect);
        child_execute(&return_, input, redirect->fd_return, ush);
    }
    kill(pid, SIGKILL);
    mx_strdel(&redirect->_stderr);
    mx_strdel(&redirect->_stdout);
    free(redirect);
    mx_free_void_arr((void**)input, mx_count_arr_el(input));
    return return_;
}
