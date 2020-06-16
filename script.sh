#!/bin/zsh
echo "1: echo "NzHHhRPB7wSpCluGslu94wwbUSf14EGIYPki0wp8T6uhHOIDFZZY2qNdmINDlEXNNctME4ejCUUJLb1sdQUP5sXy7EpThX4NiKuHDT11XRUyu8zldkPAyZybLv" (\n"
echo "echo "NzHHhRPB7wSpCluGslu94wwbUSf14EGIYPki0wp8T6uhHOIDFZZY2qNdmINDlEXNNctME4ejCUUJLb1sdQUP5sXy7EpThX4NiKuHDT11XRUyu8zldkPAyZybLv"" | ./ush > test1
echo "echo "NzHHhRPB7wSpCluGslu94wwbUSf14EGIYPki0wp8T6uhHOIDFZZY2qNdmINDlEXNNctME4ejCUUJLb1sdQUP5sXy7EpThX4NiKuHDT11XRUyu8zldkPAyZybLv"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "2: echo -n "4MjS0G5hDPhjKAh7n7rd16UjyMUh6DmacyLXBTzanRdl3N4luMW3PbqYOp0Dsdxxuwh3n2Hkvcov8uyBnSE7ykUBYHjkiZuikSmZwTdPTf3TUJYJOOmkUiAzHonZeOjCuEnSSlcd" (\n"
echo "echo -n "4MjS0G5hDPhjKAh7n7rd16UjyMUh6DmacyLXBTzanRdl3N4luMW3PbqYOp0Dsdxxuwh3n2Hkvcov8uyBnSE7ykUBYHjkiZuikSmZwTdPTf3TUJYJOOmkUiAzHonZeOjCuEnSSlcd"" | ./ush > test1
echo "echo -n "4MjS0G5hDPhjKAh7n7rd16UjyMUh6DmacyLXBTzanRdl3N4luMW3PbqYOp0Dsdxxuwh3n2Hkvcov8uyBnSE7ykUBYHjkiZuikSmZwTdPTf3TUJYJOOmkUiAzHonZeOjCuEnSSlcd"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "3: echo "\t  \v \a yZhF \v  \toIIb4uP4 \a" (\n"
echo "echo "\t  \v \a yZhF \v  \toIIb4uP4 \a"" | ./ush > test1
echo "echo "\t  \v \a yZhF \v  \toIIb4uP4 \a"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "4: which -s echo; echo $? (\n"
echo "which -s echo; echo $?" | ./ush > test1
echo "which -s echo; echo $?" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "5: cd .. ; pwd (\n"
echo "cd .. ; pwd" | ./ush > test1
echo "cd .. ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "6: cd / ; pwd (\n"
echo "cd / ; pwd" | ./ush > test1
echo "cd / ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "7: cd ../../../ ; cd - ; cd .. ; pwd (\n"
echo "cd ../../../ ; cd - ; cd .. ; pwd" | ./ush > test1
echo "cd ../../../ ; cd - ; cd .. ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "8: cd .. ; cd . ; pwd (\n"
echo "cd .. ; cd . ; pwd" | ./ush > test1
echo "cd .. ; cd . ; pwd " | zsh > test2
diff test1 test2
echo "\n)\n"
echo "9: cd /tmp ; pwd -L (\n"
echo "cd /tmp ; pwd -L" | ./ush > test1
echo "cd /tmp ; pwd -L" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "10: cd /tmp ; pwd -P (\n"
echo "cd /tmp ; pwd -P" | ./ush > test1
echo "cd /tmp ; pwd -P" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "11: cd .. ; echo "$(pwd)" (\n"
echo "cd .. ; echo "$(pwd)"" | ./ush > test1
echo "cd .. ; echo "$(pwd)"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "12: cd .. ; echo "`echo \`pwd\``" (\n"
echo "cd .. ; echo "`echo \`pwd\``"" | ./ush > test1
echo "cd .. ; echo "`echo \`pwd\``"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "13: echo ${SHLVL} ${HOME} ${LOGNAME} ${USR} ${TERM} (\n"
echo "echo ${SHLVL} ${HOME} ${LOGNAME} ${USR} ${TERM}" | ./ush > test1
echo "echo ${SHLVL} ${HOME} ${LOGNAME} ${USR} ${TERM}" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "14: cd ~ ; pwd (\n"
echo "cd ~ ; pwd" | ./ush > test1
echo "cd ~ ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "15: export UNIT=location; export UFK=p2p ucode=cbl; echo $UNIT $UFK $ucode; (\n"
echo "export UNIT=location; export UFK=p2p ucode=cbl; echo $UNIT $UFK $ucode;" | ./ush > test1
echo "export UNIT=location; export UFK=p2p ucode=cbl; echo $UNIT $UFK $ucode;" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "PART 2 ASSESSMENT"
echo "1: ucode(\n"
echo "ucode" | ./ush > test1
echo "ucode" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "2: /bin/ls (\n"
echo "/bin/ls" | ./ush > test1
echo "/bin/ls" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "3: /bin/ls -laF (\n"
echo "/bin/ls -laF" | ./ush > test1
echo "/bin/ls -laF" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "4: echo "CBL World" (\n"
echo "echo "CBL World"" | ./ush > test1
echo "echo "CBL World"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "5: /bin/echo "CBL World" (\n"
echo "/bin/echo "CBL World"" | ./ush > test1
echo "/bin/echo "CBL World"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "6: echo CBL World(\n"
echo "echo CBL World" | ./ush > test1
echo "echo CBL World" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "7: echo -n "\a" (\n"
echo "echo -n "\a"" | ./ush > test1
echo "echo -n "\a"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "8: echo "This \n must \t still \v work correctly." (\n"
echo "echo "This \n must \t still \v work correctly."" | ./ush > test1
echo "echo "This \n must \t still \v work correctly."" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "9: echo -E "This \n must \t still \v work correctly"(\n"
echo "echo -E "This \n must \t still \v work correctly"" | ./ush > test1
echo "echo -E "This \n must \t still \v work correctly"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "10: echo -e "rm -rf c:\\windows" (\n"
echo "echo -e "rm -rf c:\\windows"" | ./ush > test1
echo "echo -e "rm -rf c:\\windows"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "11: (\n"
echo "echo -E "rm -rf c:\windows"" | ./ush > test1
echo "echo -E "rm -rf c:\windows"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "12: cd /specify/the/absolute/path ; /bin/pwd ; pwd (\n"
echo "cd /specify/the/absolute/path ; /bin/pwd ; pwd" | ./ush > test1
echo "cd /specify/the/absolute/path ; /bin/pwd ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "13: cd specify/the/relative/path ; /bin/pwd (\n"
echo "cd specify/the/relative/path ; /bin/pwd" | ./ush > test1
echo "cd specify/the/relative/path ; /bin/pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "14: cd ; pwd(\n"
echo "cd ; pwd" | ./ush > test1
echo "cd ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "15: cd - ; pwd(\n"
echo "cd - ; pwd" | ./ush > test1
echo "cd - ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "16: cd ~/specify/the/path ; /bin/pwd (\n"
echo "cd ~/specify/the/path ; /bin/pwd" | ./ush > test1
echo "cd ~/specify/the/path ; /bin/pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "17: cd -s /tmp(\n"
echo "cd -s /tmp" | ./ush > test1
echo "cd -s /tmp" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "18: cd /tmp ; pwd -P (\n"
echo "cd /tmp ; pwd -P" | ./ush > test1
echo "cd /tmp ; pwd -P" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "19: cd -P /tmp ; pwd (\n"
echo "cd -P /tmp ; pwd" | ./ush > test1
echo "cd -P /tmp ; pwd" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "20: cd /var ; pwd -L ; pwd -P (\n"
echo "cd /var ; pwd -L ; pwd -P" | ./ush > test1
echo "cd /var ; pwd -L ; pwd -P" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "21: env(\n"
echo "env" | ./ush > test1
echo "env" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "22: env -i emacs ; echo $? (\n"
echo "env -i emacs ; echo $?" | ./ush > test1
echo "env -i emacs ; echo $?" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "23: env -u TERM emacs (\n"
echo "env -u TERM emacs" | ./ush > test1
echo "env -u TERM emacs" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "24: env -P / ls (\n"
echo "env -P / ls" | ./ush > test1
echo "env -P / ls" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "25: which -s something ; echo $?(\n"
echo "which -s something ; echo $?" | ./ush > test1
echo "which -s something ; echo $?" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "26: which -s env(\n"
echo "which -s env" | ./ush > test1
echo "which -s env" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "27: which -a echo(\n"
echo "which -a echo" | ./ush > test1
echo "which -a echo" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "28: export ucode=cbl ; env ; unset ucode ; env (\n"
echo "export ucode=cbl ; env ; unset ucode ; env" | ./ush > test1
echo "export ucode=cbl ; env ; unset ucode ; env" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "29: date (\n"
echo "date" | ./ush > test1
echo "date" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "30: unset PATH ; date (\n"
echo "unset PATH ; date" | ./ush > test1
echo "unset PATH ; date" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "31: ; (\n"
echo ";" | ./ush > test1
echo ";" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "32: echo 1 ; pwd ; echo 2 ; ls ; echo 3 ; ls -l (\n"
echo "echo 1 ; pwd ; echo 2 ; ls ; echo 3 ; ls -l" | ./ush > test1
echo "echo 1 ; pwd ; echo 2 ; ls ; echo 3 ; ls -l" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "33: ls ~ (\n"
echo "ls ~" | ./ush > test1
echo "ls ~" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "34: ls ~xlogin/Desktop(\n"
echo "ls ~xlogin/Desktop" | ./ush > test1
echo "ls ~xlogin/Desktop" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "35: echo `whoami` (\n"
echo "echo `whoami`" | ./ush > test1
echo "echo `whoami`" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "36: echo "$(echo -n "Ave, Caesar"), $(echo -n "morituri te salutant!")" (\n"
echo "echo "$(echo -n "Ave, Caesar"), $(echo -n "morituri te salutant!")"" | ./ush > test1
echo "echo "$(echo -n "Ave, Caesar"), $(echo -n "morituri te salutant!")"" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "37: "The user ${USER} is on a ${SHLVL} shell level."(\n"
echo ""The user ${USER} is on a ${SHLVL} shell level."" | ./ush > test1
echo ""The user ${USER} is on a ${SHLVL} shell level."" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "38: echo $PATH(\n"
echo "echo $PATH" | ./ush > test1
echo "echo $PATH" | zsh > test2
diff test1 test2
echo "\n)\n"
echo "39: echo aaa && echo bbb (\n"
echo "echo aaa && echo bbb" | ./ush > test1
echo "echo aaa && echo bbb" | zsh > test2
diff test1 test2
echo "\n)\n"
