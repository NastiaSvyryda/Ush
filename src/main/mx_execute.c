#include <ush.h>

int mx_ush(char **input) {
    extern char **environ;

    if (execve("/Users/asvyryda/Desktop/Ush/ush", input, environ) != -1)
        return 0;
    else
        return 1;//change directory
}

static int is_builtin(char *command) {
    char builtins[][10] = {"cd", "pwd", "env", "ush", "export",
                           "unset", "exit", "which", "echo"};
    char *low_com = mx_strdup(command);
    int num = 0;

    for (int i = 0; i < mx_strlen(command); i++)
        low_com[i] = (char)mx_tolower(low_com[i]);
    for (int i = 0; i < 9; i++) {
        if (mx_strcmp(builtins[i], low_com) == 0)
            num = i + 1;
    }
    mx_strdel(&low_com);
    return num;
}

static char *coomand_in_path(char *command) {
    char **path = mx_strsplit(MX_PATH(), ':');
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
    //mx_printstr(command_p);
    return command_p;
}

int mx_execute(char **input) {
    pid_t pid;
    extern char **environ;
    errno = 0;
    int return_ = 0;
    int command = is_builtin(input[0]);
    char *command_p = coomand_in_path(input[0]);
    char *output = mx_strnew(CHAR_MAX - 1);
    int fd[2];
    char *ret_ = mx_strnew(1);
    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    pid = fork();
    if (pid != 0) {
        if (command == 1)
            return_ = mx_cd(input);
        else if (command == 5)
            return_ = mx_export(input);
        else if (command == 6)
            return_ = mx_unset(input);
        else if (command == 7) {
            return_ = mx_exit(input);
        }
        wait(NULL);
        close(fd[1]);
        read(fd[0], ret_, 1);
        mx_printstr(ret_);
        close(fd[0]);
    }
    else {
        if (command == 2) {
            return_ = mx_pwd(input);
        }
        else if (command == 3)
            return_ = mx_env(input);
        else if (command == 4)
            return_ = mx_ush(input);
        else if (command == 0) {
            if (mx_file_exist(command_p)) {
                int exec = execve(command_p, input, environ);
                if (exec == -1 && errno == EACCES) {
                    fprintf(stderr, "ush: Permission denied:%s\n", input[0]);
                    return_ = 1;
                }
            }
            else {
                fprintf(stderr, "ush: %s: command not found\n", input[0]);
                return_ = 1;
            }
        }
        close(fd[0]);
        char *ret = mx_itoa(return_);
        write(fd[1], ret, strlen(ret));
        mx_strdel(&ret);
        close(fd[1]);
        exit(0);
    }
    mx_strdel(&command_p);
    mx_strdel(&output);
    if (mx_atoi(ret_) == 1 || return_ == 1)
        return_ = 1;
    else
        return_ = 0;
    return return_;
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

}

