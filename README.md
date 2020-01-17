# 21sh
`21sh is the second project dedicated to the realization of a fully functional shell in C language.`

Through the Minishell project, you will get to the core of the Unix system and explore an important part of this system’s API: process creation and synchronisation. Executing a command inside a shell implies creating a new process, which execution and final state will be monitored by its parent’s process.

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
