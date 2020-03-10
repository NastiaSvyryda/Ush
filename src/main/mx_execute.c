#include <ush.h>

int mx_ush(char **input, char *ush_path) {
    extern char **environ;

    //mx_printstr(ush_path);
    mx_strdel(&input[0]);
    input[0] = mx_strdup(ush_path);
    if (execve(ush_path, input, environ) != -1)
        return 0;
    else
        return 1;//change directory
}

 char *mx_coomand_in_path(char *command, char *str_path) {
    char **path = mx_strsplit(str_path, ':');
    char *command_p = NULL;
    int paths = mx_count_arr_el(path);

    for (int i = 0; i < mx_count_arr_el(path); i++) {
        command_p = mx_strnew(mx_strlen(command) + mx_strlen(path[i]) + 1);
        mx_strcpy(command_p, path[i]);
        command_p = mx_strcat(command_p, "/");
        command_p = mx_strcat(command_p, command);
        if (mx_file_exist(command_p))
            break;
        mx_strdel(&command_p);
    }
    mx_free_void_arr((void**)path, paths);
    if (command_p == NULL)
        command_p = mx_strdup(command);
    return command_p;
}

static void par_execute(int *ret_val, int *fd, char **input) {
    int command = mx_is_builtin(input[0]);
    char *ret_str = mx_strnew(1);

    if (command == 1)
        *ret_val = mx_cd(input);
    else if (command == 5)
        *ret_val = mx_export(input);
    else if (command == 6)
        *ret_val = mx_unset(input);
    else if (command == 7)
        *ret_val = mx_exit(input);
    wait(NULL);
    mx_read_from_pipe(ret_str, 1, fd);
    if (mx_atoi(ret_str) == 1 || *ret_val == 1)
        *ret_val = 1;
    else
        *ret_val = 0;
    mx_strdel(&ret_str);
}

static void child_execute(int *ret_val, char **input, int *fd, char *ush_path) {//убрать return_pipe
    int command = mx_is_builtin(input[0]);
    char *command_p = mx_coomand_in_path(input[0], MX_PATH());
    extern char **environ;
    char *ret = NULL;
    errno = 0;

    if (command == 2)
        *ret_val = mx_pwd(input);
    else if (command == 3)
        *ret_val = mx_env(input);
    else if (command == 4)
        *ret_val = mx_ush(input, ush_path);
    else if (command == 0) {
        if (mx_file_exist(command_p)) {
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
    ret = mx_itoa(*ret_val);
    mx_write_to_pipe(ret, fd);
    mx_strdel(&ret);
    mx_strdel(&command_p);
    exit(0);
}

static t_redirect *create_redirect(void) {
    t_redirect *redirect = malloc(sizeof(t_redirect));
    redirect->_stderr = mx_strnew(1000);
    redirect->_stdout = mx_strnew(1000);
    pipe(redirect->fd_return);
    pipe(redirect->fd_stdout);
    pipe(redirect->fd_stderr);
    return redirect;
}

int mx_execute(char *str_input, int flag_redirect, char *ush_path) {
    pid_t pid;
    int return_ = 0;
    char **input = mx_strsplit(str_input, ' ');
    t_redirect *redirect = create_redirect();
    pid = fork();
    if (pid != 0) {
        par_execute(&return_, redirect->fd_return, input);
        if (flag_redirect == 1)
            mx_read_from_pipe(redirect->_stdout, 1000, redirect->fd_stdout);
        mx_read_from_pipe(redirect->_stderr, 1000, redirect->fd_stderr);
        if (mx_strlen(redirect->_stderr) != 0) {
            return_ = 1;
            mx_printstr(redirect->_stderr);
        }
    }
    else {
        if (flag_redirect == 1) {
            if (dup2(redirect->fd_stdout[1], 1) == -1)
                perror("dup2");
            close(redirect->fd_stdout[0]);
        }
        if (dup2(redirect->fd_stderr[1], 2) == -1)
            perror("dup2");
        close(redirect->fd_stderr[1]);
        child_execute(&return_, input, redirect->fd_return, ush_path);
    }
    mx_strdel(&redirect->_stderr);
    mx_strdel(&redirect->_stdout);
    free(redirect);
    mx_free_void_arr((void**)input, mx_count_arr_el(input));
    return return_;
}

//    int term_fd = open("/dev/tty", O_WRONLY);
//    if (term_fd == -1)
//        perror("open");
//    if (dup2(term_fd, 1) == -1)
//        perror("open");
//    close(term_fd);

//    char ch;
//    int myfile = open ("/dev/tty", O_RDONLY);
//    while(read(myfile, &ch, 1))
//        mx_printchar(ch);
//    mx_printchar('\n');
//    close(myfile);

