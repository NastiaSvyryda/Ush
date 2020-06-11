#include "ush.h"

static void if_tidle(char **inp, char *home, char *pwd) {
    char *tmp = mx_strdup(*inp);

    if (mx_isalpha((*inp)[1])) {
        mx_strdel(inp);
        *inp = mx_replace_substr(tmp, "~", "/Users/");
    }
    else if ((*inp)[1] == '/' || (*inp)[1] == '\0') {
        mx_strdel(inp);
        *inp = mx_replace_substr(tmp, "~", home);
    }
    else if ((*inp)[1] == '+' && ((*inp)[2] == '/' || (*inp)[2] == '\0')) {
        mx_strdel(inp);
        *inp = mx_replace_substr(tmp, "~+", pwd);
    }
    else if ((*inp)[1] == '-' && ((*inp)[2] == '/' || (*inp)[2] == '\0')) {
        if (MX_OLDPWD() != NULL) {
            mx_strdel(inp);
            *inp = mx_replace_substr(tmp, "~-", MX_OLDPWD());
        }
    }
    mx_strdel(&tmp);
}
static void tidle_check(char **input) {//temporary for all
    char *home = mx_strdup("");
    char *pwd = MX_PWD();

    if (getenv("HOME") != NULL) {
        mx_strdel(&home);
        home = MX_HOME();
    }
    if_tidle(input, home, pwd);
    mx_strdel(&home);
    mx_strdel(&pwd);
}

static char *dollar_change(int len, char **input) {
    char *variable = NULL;

    if ((*input)[1] == '{' && (*input)[len - 1] == '}') {
        variable = mx_strnew(len - 1);
        for (int y = 2, x = 0; y < len - 1; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 3] = '=';
        variable[len - 2] = '\0';
    }
    else {
        variable = mx_strnew(len + 1);
        for (int y = 1, x = 0; y < len; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 1] = '=';
        variable[len] = '\0';
    }
    return variable;
}

static void dollar_check(int len, char **in) {
    char *var = NULL;
    extern char **environ;
    int x = 0;
    int flag = 0;

    var = dollar_change(len, in);
    for (int j = 0; environ[j]!= NULL; j++) {
        if (strstr(environ[j], var) != NULL && environ[j][0] == var[0]) {
            flag = 1;
            mx_strdel(in);
            (*in) = mx_strnew(mx_strlen(environ[j]) - mx_strlen(var) + 1);
            x = 0;
            for (int y = mx_strlen(var); y <= mx_strlen(environ[j]); y++)
                (*in)[x++] = environ[j][y];
            (*in)[x] = '\0';
            break;
        }
    }
    mx_strdel(&var);
    if (flag == 0) {
        mx_strdel(in);
        (*in) = mx_strdup("");
    }
//    mx_printstr(*in);
//    mx_printchar('\n');
}

static void insert_chars(char **str, char sym, int index) {
    char temp;
    int len = mx_strlen(*str);

    (*str) = realloc((*str), len + 2);
    for (; index < len + 1; index++) {
        temp = (*str)[index];
        (*str)[index] = sym;
        sym = temp;
    }
    (*str)[index] = '\0';
}

char **mx_split_echo(char *str_input, int check, int start, int end) {
    char **arr = NULL;
    if (check == 2) {
        arr = mx_strsplit(str_input, '\'');
        insert_chars(&(arr[start]), '\'', 0);
        insert_chars(&(arr[end]), '\'', mx_strlen(arr[end]));
    }
    else {
        arr = mx_strsplit(str_input, '\"');
        insert_chars(&(arr[start]), '\"', 0);
        insert_chars(&(arr[end]), '\"', mx_strlen(arr[end]));
    }
    mx_strdel(&arr[0]);
    arr[0] = mx_strdup("echo");
    return arr;

//    int size = mx_count_words(str_input, ' ');
//    char **result = (char**) malloc(sizeof(char*) * (size + 1));
//    int begin = 0;
//
//    for (int i = 0; i < size; i++) {
//
//    }
//    result[size] = NULL;
//    return result;
}

int mx_check_echo(char **n, int *start, int *end) {
    int flag_one = 0;
    int flag_two = 0;
    int len = 0;

    if (mx_strcmp(n[0], "echo") == 0 || mx_strcmp(n[0], "/bin/echo") == 0) {
        for (int i = 0; i < mx_count_arr_el(n); i++) {
            len = mx_strlen(n[i]) - 1;
            if (n[i][0] == '-')
                continue;
            else if (n[i][0] == '\'' || n[i][len] == '\"') {
                if (n[i][0] == '\'')
                    *start = i;
                if (n[i][len] == '\'')
                    *end = i;
                flag_one++;
            }
            else if (n[i][0] == '\"' || n[i][len] == '\'') {
                if (n[i][0] == '\"')
                    *start = i;
                if (n[i][len] == '\"')
                    *end = i;
                flag_one++;
                flag_two++;
            }
        }
    }
    if (flag_one % 2 == 0 && flag_two % 2 == 0) {
        if (flag_one != 0)
            return 2;
        return -2;
    }
    return 0;
}

char **mx_check_expansion(char *str_input, int ret_val) {
    int len = 0;
    char **input = mx_strsplit(str_input, ' ');
    //
    int start = 0;
    int end = 0;
    int check = mx_check_echo(input, &start, &end);

    if (check != 0) {
        mx_free_void_arr((void **)input, mx_count_arr_el(input));
        input = mx_split_echo(str_input, check, start, end);
    }
    for (int i = 0; i < mx_count_arr_el(input); i++) {
        if (mx_get_substr_index(input[i], "$?") >= 0) {
            mx_strdel(&input[i]);
            input[i] = mx_itoa(ret_val);
        }
        if (input[i][0] == '~')
            tidle_check(&input[i]);
        len = mx_strlen(input[i]);
        if (input[i][0] == '$')
            dollar_check(len, &input[i]);
    }
    return input;
}
