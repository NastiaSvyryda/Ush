#include "ush.h"

static int par_exec_command(char **input, int *exit_status) {
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    int command = mx_is_builtin(command_p);
    int ret_val = 0;

    if (command == 1)
        ret_val = mx_cd(input);
    else if (command == 5)
        ret_val = mx_export(input);
    else if (command == 6)
        ret_val = mx_unset(input);
    else if (command == 7)
        ret_val = mx_exit(input, exit_status);
    mx_strdel(&command_p);
    return ret_val;
}

static void fill_jobs(pid_t pid, t_ush *ush) {
    t_pid *temp = NULL;
    if (ush->pids != NULL) {
        temp = ush->pids;
        ush->pids = ush->pids->next;
    }
    ush->pids = (t_pid *) malloc(sizeof (t_pid));
    ush->pids->num = pid;
    ush->pids->index++;
    ush->pids->str = mx_strdup(ush->str_input);
    ush->pids->prev = temp;
    ush->pids->next = NULL;
}

static void check_for_redirect(int *ret_val, int *fd, t_redirect *redirect, t_ush *ush, pid_t pid) {
    char *ret_str = mx_strnew(1);
    int status = 0;
    int pid_i = -1;
    char **input = mx_strsplit(ush->str_input, ' ');

    if (mx_strcmp(input[0], "fg") == 0 && ush->pids != NULL) {
        pid_i = ush->pids->num;
        mx_strdel(&ush->str_input);
        ush->str_input = mx_strdup(ush->pids->str);
    }
    waitpid(pid_i, &status, WUNTRACED);
    if(!WIFSTOPPED(status)) {
        mx_read_from_pipe(ret_str, 1, fd);
        mx_parent_redirect(redirect, ret_val);
    }
    if(WIFSTOPPED(status)) {
        *ret_val = 146;
        printf("\nush: suspended  %s\n", ush->str_input);
        fill_jobs(pid, ush);
    }
    else if (mx_atoi(ret_str) == 1 || *ret_val == 1)
        *ret_val = 1;
    else
        *ret_val = 0;
    mx_strdel(&ret_str);
    mx_free_void_arr((void **) input, mx_count_arr_el(input));
}

//void siga() {
//    int i = 0;
//    kill(getpid(), SIGKILL);
//    mx_parent_redirect(fd, redir, &i);
////    signal(SIGTSTP, SIG_DFL);
//}

int mx_execute(t_ush *ush, char *str_input, int flag_redirect, char **str_red) {
    pid_t pid;
    int return_ = 0;
    char **input = mx_check_expansion(str_input, ush->return_value);
    t_redirect *redirect = mx_create_redirect();
    redirect->flag = flag_redirect;
    ush->str_input = str_input;

    pid = fork();
    if (pid != 0) {
        //mx_printint(pid);
        return_ = par_exec_command(input, &ush->exit_status);
        check_for_redirect(&return_, redirect->fd_return,
                           redirect, ush, pid);
    }
    else {
        signal(SIGTSTP, SIG_DFL);
        mx_child_redirect(redirect);
        mx_child_execute(&return_, input, redirect->fd_return, ush);
    }
    if (redirect->_stdout != NULL && flag_redirect == 1) {
        if (redirect->_stdout[mx_strlen(redirect->_stdout) - 1] == '\n')
            redirect->_stdout[mx_strlen(redirect->_stdout) - 1] = '\0';
        *str_red = mx_strdup(redirect->_stdout);
    }
    mx_strdel(&redirect->_stderr);
    mx_strdel(&redirect->_stdout);
    free(redirect);
    mx_free_void_arr((void**)input, mx_count_arr_el(input));
    return return_;
}
