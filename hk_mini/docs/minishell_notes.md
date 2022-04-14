MINISHELL NOTES

the main arguments not only contains argc, argv but also envp array
```c
int main (int argc, char *argv[], char *envp[])
```
*envp array contains the program's environment. (but according to gnu.org
POSIX.1 doesn't allow this three argument form, so for portability it is
best to write main to take two arguments and use the value environ.)
to use environ just declare (it is a char *environ[])
```c
extern char **environ; 	//extern is telling the compiler that environ has been 
						//declared some where else.
```
---

* Need to install new version of readline through brew  
	```shell 
	brew install readline
	```
	when compiling use the following :  
	export LDFLAGS="-L/Users/hman/.brew/opt/readline/lib"  
	export CPPFLAGS="-I/Users/hman/.brew/opt/readline/include"  
	or  
	`-L$(brew --prefix readline)/lib -lreadline -I$(brew --prefix readline)/include`  
	the `brew --prefix readline` will replace it with the directory where readline has been installed by brew in your case it would have been `/Users/hman/.brew/opt/readline`  
	(NOTE: in the makefile you use `-L(shell brew --prefix readline)/lib`)  
	
	you can use `\<readline/readline.h\>` or `"readline/readline.h"` 
* on linux you have to install readline library. On Ubuntu you can do that with
	```shell
	sudo apt-get install libreadline-dev
	```
* REMEMBER TO COMPILE WITH THE NEW READLINE library. The old readline library for some reason will enable ECHOCTL again when using it. The new readline library will take the current state of the terminal and the old one won't.
* But the assignment don't allow more than one global variable. So using the \*envp\[\] would be best, even though it is not POSIX complaint.
* to check whether a file exist you can use stat() function. if it doesn't exist it will return 0.
* remember that starting a shell inside minishell could fail because the STDIN and STDOUT has been overwritten in piping. So make sure that is not the case.
* CTRL + \ will create a SIGQUIT signal that will quit the foreground process. in minishell should nothing and not quit minishell.
* When starting the minishell it will get a copy of the environment variables. The minishell will manipulate this copy. Thus setting, unsetting will only apply to this copy. But adding to it will be little problem. so might be best to create a copy of it using malloc.
* remember to read the pipex notes.
* use STDIN_FILENO and STDOUT_FILENO as defined in unistd.h
* if the command is not found exit status is 127, if the command is found but not executable the exit status is 126.
* concerning global variable. in one evaluation they used the global variable to remember the process id. Apparently the pid of couldn't be returned when you kill a child process. (May not be the case in your implementation) It is specifically used to get the pid to kill a child process in heredoc for example.
* to flip a flag in the termios struct you can use the `~` bitwise operator. This is the NOT operator which will flip all the bits. 1 to 0 and 0 to 1. 
* remember that the ECHOCTL bitmask flag is different on linux than on the mac
* Apparently whenever a pipe is involved in the command input every command will be executed in a child process. Even the builtin functions. E.g. `exit | ls` will not exit because exit will be run in a child process. (We don't have to implement it but with `;` this is not the case. Apparently only when the builtin function is part of a pipe)
* exit code when using CTRL-C and CTRL-\ on programs that requires input are 130 and 131 respectively (e.g. cat)
* exit code when CTRL-C on shell prompt will be 1.
* signals when starting child processes, disable the signals on the parent and fork and then re-enable them on the child.

**TEST CASE**
* `cat | cat | ls` should print ls then the first cat should run and end after the first newline and the second cat should run and end after the newline.
But it works on your current pipex so it should be fine.

---

**readline**

* compile readline with -lreadline and include readline/readline.h readline/history.h
* use the new readline library to that is installed with brew to be able to use the new readline functions. The readline functions are only available on the new readline library.
* to add history
```c
	#define PROMPT "minishell>"

	s = readline(PROMPT);
	printf("%s\n",s);
	add_history(s);
	free(s);
```

* readline will return NULL when EOF is reached. if not it will contain the string without '\\n'
* if there are still characters in te inputline and EOF is pressed by CTRL-D then nothing happens. Only when the only input is EOF will the readline be NULL.

also don't add an empty string to the history because it isn't very usefull
---

**free malloced memory inherited from parent in child**

when using fork() remember that any malloc-ed heap memory is also copied to the child (although it will be shared memory if the child will not write to it. If the child write to it, it will do copy-on-write and thus be its own memory.) So you have to free the malloc-ed memory. Unless you are using execv, this function will replace the child program and automatically free all the heap memory assigned to the child process.

---

**exit**

the exit builtin function should display the exit code that has been given. e.g. `exit 1` will exit with exit code 1 .  
if no argument is provided it will exit with the exit code of the last command executed.  
**edge cases** :  
`exit 1 a` will not exit but display error : `too many arguments`
`exit a 1` will exit but display error : numeric argument required.
Basically if the first argument is a numeric, but has more than 1 argument it will complain too many arguments and not exit. But if the first argument is not numeric it will exit but complain about it not being numeric but set the exit code too 255

exit code first go through a remainder of 256 (% 256). if exit code is 256 the exit code becomes 0 and 1 if exit code is 257. if the exit code is 266 => exit code will be 10  
if exit code is -2 => exit code will be 254

in bash if exit is called after a pipe only the child process will exit and thus the main process will not exit.

exit will also print exit to STDERR. 

`exit | ls` will run ls and not exit (apparently when pipes are involved everything is in a child process).

EDGE CASE: 'exit | exit` will not exit bash and also not print anything. 

---

**signals**:

CTRL-C = SIGINT  
CTRL-\ = SIGQUIT  
CTRL-D = EOF (the readline will return NULL)  

```c
static void	init_terminal(t_data *data)
{
	if (isatty(STDIN_FILENO)) //test if stdin is an terminal
		tcgetattr(0, &data->old_term); //copy attributes of old term
	data->new_term = data->old_term; //set new term to old term
	data->new_term.c_lflag &= ~(ECHOCTL); //disable echo ctrl and don't print CTRL in the new term
	if (isatty(STDIN_FILENO))
		tcsetattr(0, TCSANOW, &data->new_term); //set the terminal to the attributes of the new term.
}
```
https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_signals.htm

in heredoc the CTRL still shouldn't be printed. but during programs like cat. it should still print thus you need to remember to set the terminal to print CTRL when not in terminal. Need more test on this to be sure. Because on the mac it still prints it for some reason.


---

**redirections**

Redirections are processed in the order they appear, from left to right. Pipe redirection will be done first (if any) than the redirection according to order. The last redirection is the one that will be used. e.g. `<inputfile <<END` the heredoc will be used for input and in `<<END <inputfile` the inputfile will be used for input. In general all of the redirection will be applied and thus the last one will be left. The same goes for output redirection that is why in `>out >out1 >out2` will create all 3 files and the last one will be used. This is the case with bash. Zsh behave differently but we need to use bash as reference.
 
---

**heredoc**

heredoc: could be implemented by writing it to a file and then open the file to read from it. Using dup2 to replace STDIN. Bash also create a temporary file and read from it instead of STDIN. according to https://www.oilshell.org/blog/2016/10/18.html
 
 An alternative is using a pipe to do it, so you don't have to clean up the tmp file. The only problem is that the pipe might get full and it will block writing. The pipe buffer size is about 65536 bytes. about 64kb. This should be more than enough to accommadate a heredoc. 

when multiple heredocs each one are run sequencially from left to right. e.g. `<<END cat | <<END2 cat`. The first heredoc will be active to end it use END and the second one is active and use END2. 

from experimentation heredoc seems to be executed first before all redirections and commands. So create all the here doc documents first and then use the heredoc document during redirections. And than maybe unlink them at the end.

idea: When starting each heredoc, maybe use waitpid on to see if it ended by signal and continue with that information.ß
The WIFSIGNALED macro is always successful.

If the child process for which status was returned by the wait or waitpid function exited because it raised a signal that caused it to exit, the WIFSIGNALED macro evaluates to TRUE and the WTERMSIG macro can be used to determine which signal was raised by the child process. Otherwise, the WIFSIGNALED macro evaluates to FALSE.

if CTRL-C is pressed on heredoc the exit code will be set to 1

---

**shell variables**

only export will be used to set variables. We don't have to implement local variables

---

**notes on built-in functions**

* basically all the basic functions should be executed by main program so the changes will keep as long the minishell program runs. 

* **cd**: if cd is the first command it needs to executed in the main program and not in a child process. If done in child process the changed directory has no effect on the main program.


___

# Subject of minishell

* only one global variable (most people use it for SIGNAL)
* Not intrepret unclosed quotes or unspecified special characters like \ or ;.
* Show prompt when waiting for a new command
* working history (readline)
* search and launch the right executable (based on the PATH variable or by using relative or absolute path)

* builtins to implement:
	* echo with option -n (removes the newline after printing)
	* cd with only a relative or absolute path
	
	* pwd with no options (display current working directory (note: PWD is the current working directory when the process is started, but it is constant. process. cwd() is asking the underlying system for the process's current directory, which can be changed with process.)
	* export with no options (will export a variable to the environment variables of the current active shell) Each shell has its own environment environment (start with copy of the other shell where it started)
	* unset with no options (will remove a environment variable)
	* env with no options or arguments (will display the environment variables)
	* exit with no options (exit the shell)
* ' inhibit all interpretation of a sequence of characters
* " inhibit all interpretation of a sequence of characters exepct for $
* Redictions:
	* < should redirect input
	* \> should redirect output
	* << read input from the current source until a line containing only the delimiter is see. it doesn't update history
	* \>\> should redirect output to append mode
* Pipes | The output of each command in the pipelin is connected via a pipe to the input of the next command. 
* environment variables ($ followed by characters) should expand to their values
* handle $? which should expand to the exit status of the most recently executed foreground pipeline.
* in interactive mode:
	* ctrl-C display a new prompt on a new line
	* ctrl-D exits the shell
	* ctrl-\ does nothing

---

Some definitions:
 
*  **control operator**: A token that performs a contol function. It is a newline or one of the following: `||` , `&&` , `&` , `;` , `;;` , `;&` , `;;&` , `|` , `|&` , `(` , or `)` . In this case only `|` need to implemented
* **field** : A unit of text that is the result of one of the shell expansions. After expansion, when exectuing a command, the resulting fields are used as the command name and arguments. 
* **metacharacter** : A character that, when unqoted, seperates words. A metacharacter is a **space**, **tab**, **newline**, or 
one of the following characters: `|` , `&` , `;` , `(` , `)` , `<` , `>`. In this case **space**, **tab**, **newline**, `|`, `<` , `>`
* **operator** : A control operator or a rediction operator. Operators contain at least one unqouted metacharacter.
* **token** : a sequence of characters considered a single unit by the shell. It is either a **word** or an **operator**.
* **word** : a sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

---

Shell operations :
1. input from file or terminal
2. break input into words and operators, obeying the quoting rules. These tokens are seperated by metacharacter. 
3. Parses the tokens into simple and compound commands(e.g.conditional loop). We only need to do simple commands.
4. Performs the various shell expansions, breaking the epanded tokens into list of filenames and commands and arguments.
5. Performs any necessary redirections and removes the redirectin operators and their operands from the argument list.
6. executes the command.
7. Optionally waits for the command to complete and collects its exit status.

---
