# Minishell
"Going back in time to experience "problems" people faced when Windows did not exist."

A shell is a software used to communicate with a computer using interactive lines of commands in a language somewhat close to the human language. 
Most commonly used ones are [Bash](https://www.gnu.org/software/bash/), [Zsh](https://www.zsh.org/), [Korn](http://www.kornshell.com/), [Tcsh](https://www.tcsh.org/) and [Fish](https://fishshell.com/)

Minishell is based on the behaviour of the Bash shell. 

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

Run:
----
- make
- ./minishell
