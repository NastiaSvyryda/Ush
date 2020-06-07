#include "ush.h"

char *mx_getenv(char *var) {
    char *cwd = NULL;

    if (strcmp(var, "PWD") == 0) {
        if ((cwd = mx_strdup(getenv("PWD"))) == NULL)
            cwd = getcwd(NULL, 0);
        if(cwd == NULL)
            perror("getcwd() error");
        return cwd;
    }
    if (strcmp(var, "HOME") == 0) {
        struct passwd *pw = getpwuid(getuid());
        char *homedir = mx_strdup(pw->pw_dir);
        return homedir;
    }
    if (strcmp(var, "SHLVL") == 0) {
        if (getenv("SHLVL") == NULL)
            return mx_strdup("1");
        return mx_strdup(getenv("SHLVL"));
    }
    if (strcmp(var, "OLDPWD") == 0) {
        if (getenv("OLDPWD") == NULL)
            return NULL;
        return getenv("OLDPWD");
    }
    if (strcmp(var, "PATH") == 0) {
        if (getenv("PATH") == NULL)
            return "/Users/asvyryda/.brew/bin:/bin:/usr/bin:/usr/ucb:/usr/local/bin";
        return getenv("PATH");
    }
    return NULL;
}
