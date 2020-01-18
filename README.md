# 21sh
`21sh is the second project dedicated to the realization of a fully functional shell in C language.`

Thanks to the Minishell project, we discovered a part of what is behind the scene of a shell, such as the one we use everyday.
And more specifically the process’ synchronisation creation with functions like fork and wait.

The 21sh project will make us go further by adding, amoungst other things, interprocess communication using pipes.
We’ll discover termcaps. This library will allow us to add to your shell a line edition feature. We’ll then be able to
edit a typo made on our command without having to retype it completely as well as
repeat a previous command using history.

# New Features

In this project new features were added to the Minishell project , all functions already implemented in Minishell are functional in 21sh, and i added:
- separators of a command line ";" for ex `ls ; pwd ; echo hello world`
- redirections of file descriptors and here doc for ex `ls > test ; cat -e << EOF ; cat < test` 
- Multi-pipe execution for ex  `ls | cat | grep .c`
- boolean operators between commands "&&" "||"
- colored prompt like ZSH

More details in the task file [21sh]()

# How to use

Execute these commands:

`make fclean && make && ./21sh`
