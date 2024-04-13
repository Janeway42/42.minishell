# **42.Minishell**


Run:
----
- make
- ./minishell

-------------------------------------------------------------------

[42 The Network](https://www.42network.org/) Assignment:
-----------

"Going back in time to experience "problems" people faced when Windows did not exist."

A shell is a software used to communicate with a computer using interactive lines of commands in a language somewhat close to the human language. 
Most commonly used ones are [Bash](https://www.gnu.org/software/bash/), [Zsh](https://www.zsh.org/), [Korn](http://www.kornshell.com/), [Tcsh](https://www.tcsh.org/) and [Fish](https://fishshell.com/)

Minishell is based on the behaviour of the Bash shell. 

-------------------------------------------------------------------

Requirements:
-------------
- Implement redirections:
  - **<** redirects input.
  - **>** redirects output.
  - **<<** is given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
  - **>>** redirects output in append mode.
- Pipes (**|** character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handles environment variables (**$** followed by a sequence of characters) which should expand to their values.
- Handles **$?** which expands to the exit status of the most recently executed foreground pipeline.
- Handles **ctrl-C**, **ctrl-D** and **ctrl-\** which behave like in bash.
- In interactive mode:
  - **ctrl-C** displays a new prompt on a new line.
  - **ctrl-D** exits the shell.
  - **ctrl-\** does nothing.
- Implemented builtins:
  - **echo** with option **-n**
  - **cd** with only a relative or absolute path
  - **pwd** with no options
  - **export** with no options
  - **unset** with no options
  - **env** with no options or arguments
  - **exit** with no options
---
- Allowed external functions: readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
-------------------------------------------------------------------

Code format: 
------------
The code must be written in accordance to the 42 set of norms.  
These include for example a maximum of 25 lines per function, at most 80 columns per line, comments included and a maximum of five functions per file. 

-------------------------------------------------------------------


