# Ush

Implementation of shell zsh. iTerm taken as an example of a terminal. 

# DESCRIPTION

1. The default prompt looks like u$h> followed by the space character.
2. The shell deals only with one line user input. In other cases, appropriate
descriptive error message is displayed.
3. The shell implements builtin commands without flags: export, unset, fg, exit . 
4. The shell also implements the following builtin commands with flags:
- env with -i, -P, -u;
- cd with -s, -P and - argument; 
- pwd with -L, -P;
- which with -a, -s;
- echo with -n, -e, -E;
5. The shell calls the builtin command instead of binary program if there is the
     name match between them.
6. The shell correctly manages errors like other shells do.
7. The shell manages user environment correctly.
8. The shell runs programs located in the directories listed in the PATH variable.
9. The shell manages signals CTRL+D , CTRL+C and CTRL+Z .
10. The shell implements command separator ; .
11. These characters are escaped to be used literally: space , ' , " , $ , ( , ) , \,`,{,}.
12. The shell manages these expansions correctly:
- tilde expansion ~ with the following tilde-prefixes: ~ , ~/dir_name , ~username/dir_name , ~+/dir_name , ~-/dir_name ;
- the basic form of parameter expansion ${parameter} ;
- command substitution `command` and $(command) .
