
#!/bin/bash

bash_result='./bash_test/test'
minishell_result='./minishell_test/test'
counter=1

test() {
		
	printf "\e[0;36mTest\e[33m $@ \e[0m\n"
	if diff <(echo $@ | ./minishell) <(echo $@ | bash); then
	printf "\e[32mOK\e[0m\n"
	else
	printf "\e[91mKO\e[0m\n"
	fi
}

test_output_redir() {

	printf "\e[0;36mTest redirect\e[33m $@ \e[0m\n"
	echo $@ | ./minishell > "$minishell_result$counter"
	echo $@ | bash > "$bash_result$counter"
	if diff "$minishell_result$counter" "$bash_result$counter" ; then
	printf "\e[32mOK\e[0m\n"
	else
	printf "\e[91mKO\e[0m\n"
	fi
	((counter=counter+1))
}

printf "\n=========== MINISHELL TESTS ===========\n\n"

test "ls"
test "echo 123"
test "cat unset.c | grep main"
test "qwe"
test "echo 123 ; ls"
test "cd .."

test "/bin/ls"
test "/bin/date"
test "/bin/ls /bin"
test "/bin/ls -la /bin"
test "/usr/bin/grep test main.c"

test "echo"
test "echo \"\""
test "echo test"
test "echo -n test"
test "echo 123 jhagsd ydsuaft"
test "echo 123 jhagsd 		ydsuaft"
test "echo   123 		jhag	sd ydsuaft"
test "echo 123 jhagsd ydsu::aft"
test "echo 123 jhagsd yds\>uaft"
test "echo 123 jhagsd ydsuaft > 1"
test "echo \$HOME"
test "echo sdlfkjg dkjfh\ jj"
test "echo dhsfg hdgf\$HOME zfjdh"
test "echo \"dhsfg hdgf\$HOME zfjdh\""
test "echo \"dhsfg hdgf\$HOMEsdfd zfjdh\""
test "echo dhsfg hdgf\$HOMEsdfd zfjdh"
test "echo rews\d"
test "echo \"ewrf\df\""
test "echo 'qwe \ \$HOME \\\$USER	23324'"
test "echo '\ 234 ls'"
test "echo -n ls -la"
test "echo \"\$USER test\""
test "echo \$USER\$PWD"

test "cat main.c"
test "cat minishell.h | grep short | wc -l"
test "cat minishell.h | grep short | grep is | wc -l"
test "cat minishell.h | grep short | grep out | wc -l"
test "ls ert | grep 123 | wc -l"
test "ifconfig | grep en | grep 8963 | grep flags | grep UP"

test "\$?"
test "echo \$?"
test "\$?"

test "export TEST= 1"
test "export TEST = 1"
test "export TEST =1"
test "export TEST=1 TEST1 1"

# Check if 'env' shows current environment variables
# Export environment variables, create new ones and replace old ones
# Use unset to remove some of environment variables 
# Unset the PATH and check commands with relative path (ls, pwd)

test "cd .. ; pwd"
test "cd / ; pwd"
test "cd ./libft"
test "cd 123"
test "cd .. ; echo \$PWD"
test "cd /bin ; echo \$OLDPWD"

test_output_redir "ls"
test_output_redir "cat minishell.h | grep short | wc -l"
test_output_redir "cat < test_in | grep short | wc -l"
test_output_redir "cat main.c | grep short < test_in | wc -l"