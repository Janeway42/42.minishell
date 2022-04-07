# Sources

readline : https://tiswww.case.edu/php/chet/readline/readline.html



# Allowed functions descriptions


## known
printf(),malloc(),free(),write(),access(),open(),read(),close(),fork(),wait(),waitpid(), exit(),execve(), dup(), dup2(), pipe(), strerror(), perror(), unlink()

---

## wait3 and wait4

`pid_t wait3(int *wstatus, int options, struct rusage *rusage)`  
`pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);`

these functions are basically the same as waitpid() and wait() except for the extra argument rusage which is a accounting the resource usage of the child

--- 

## readline

`#include <stdio.h>`  
`#include <readline/readline.h>`  
`#include <readline/history.h>`  

`char *readline (const char *prompt);`

e.g `char *s = readline("minishell>");`

readline read a line from terminal and return it, using prompt as a prompt. line returned is allocated with malloc. must be freed. The line returned has the final newline removed.

Return : the text of the line read. blank line returns empty string. if EOF is encountered while reading a line and the line is empty, NULL is returned. If an EOF is read with a non-empty line, it is treated as a newline.

---

## rl_on_new_line (still experiment)

`int rl_on_new_line(void)`

tell the update routines that we have moved onto a new (empty) line, usually after outputting a new line.

---

## rl_replace_line (still experiment)

`void rl_replace_line(const char *text, int clear_undo)`

replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

---

## rl_redisplay

`void rl_redisplay(void)`

Change what's displayed on the screen to reflect the current contents of rl_line buffer.

---

## rl_clear_history 

`void rl_clear_history(void);`

Clear the history list by deleting all the entries in the same manner as the History library's clear_history() function. This differs from clear_history because it free private data Readline saves in the history list.

---

## add_history

`void add_history(const char *string);`

this function will add the history function to the readline. just add a line
`add_history(string);` and it will add the string to the history.
notes: if the line is empty don't add to history no use for it

---

## signal

#include <signal.h>

`void (*signal(int sig, void (*func)(int)))(int);`

this function is a simplified interface to the more general sigaction(2) facility. To use it add the line `signal(SIGXXX,&function)` it will go to the function when it catches the relevant signal. In this case SIGINT and SIGQUIT. e.g. `signal(SIGQUIT,signalhandlingfunc);`

---

## sigaction

`int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);`

the sigaction() system call assigns an action for a signal specified by sig. It act is non-zero, it specifies an action (SIG_DFL, SIG_IGN, or a handler routine) and a mask to be used when delivering the specified signal. If oact is non-zero, the previous handling information for the signal is returned to the user.

---

## sigemptyset

---

## sigaddset

---

## kill

`int kill(pid_t pid, int sig);`

function sends the signal specified by sig to pid, a process or a group of processes. Typically, Sig will be one of the signals specified in sigaction(2). A value of 0, however, will cause error checking to be performed (with no signal being sent). This can be use to check the validity of pid.

if pid is greater than zero:
	sig is sent to the process whose ID is equal to pid.

if pid is zero:
	sig is sent to all processes whose group ID is equal to the process group ID of the sender, and for which the process has permission; this is a variant of killpg(2).

if pid is -1:
	If the user has super-user privileges, teh signal is sent to all processes excluding system processes and teh process sending the signal. If the user is not the super user, the signal is sent to all processes with the same uid as the user, excluding the process seding the signal. No error is returned if any process could be signaled. 

will return 0 upon successful completion, a value of 0 is returned. Otherwise, a value of -1 is returned and errno is set.
---

## getcwd

`char *getcwd(char *buf, size_t size);`  

function copies the absolute pathname of the current working directory into the memory referenced by buf and returns a pointer to buf. The size argument is the size, in bytes of the array referenced by buf. If buff is NULL, space is allocated as necessary to store the pathname and size is ignored. THis space may later be free(3)'d

---

## chdir

`int chdir(const char *path);`  

changes the current working directory of the calling process to the directory specified in path
return 0 on success, on error it returns -1 and errno is set.

---

## stat

`int stat(const char *restrict path, struct stat *restrict buf);`  

obtains information about the file pointed to by path. Read, write, execute permission of the named file is not required, but all directories listed in the path name leading to the file must be searchable.


---

## lstat

`int lstat(const char *restrict path, struct stat *restrict buf);`

is like stat() except in the case where the named file is a symbolic link; lstat() returns information about the link, while stat() returns information about the file the link references. 

---

## fstat

`int fstat(int fildes, struct stat *buf);`

obtains the same information about an open file known by the file descriptor fildes.


---

## opendir

`DIR *opendir(const char *filename);`

opens the directory named by filename, associates a directory stream with it and returns a pointer to be used to identify the directory stream in subsequent operations. The pointer NULL is returned if file name cannot be accessed, or if it cannot malloc(3) enough memory to hold the whole ting, and sets the global variable errno to indicate the error.

---

## readdir

`struct dirent *readdir(DIR *dirp);`

function returns a pointer to the next directory entry. It returns NULL upon reaching the end of the directory or on error. In the event of an error, errno may be set to any of the values documented for the getdirentries(2) system call. 

---

## closedir

`int closedir(DIR *dirp);`

closes the named directory steram and frees the structure associated with the dirp pointer, return 0 on success. On failure, -1 is returned and the global variable errno is set to indicate the error.

---

## isatty

`int isatty(int fd);`  
determines if the file descriptor fdrefers to a valid terminal type device. if the fd is a tty then it will return 1 else it will return 0 and set errno

---

## ttyname

`char *ttyname(int fd);`  
returns the name of the terminal on the fd e.g. `/dev/ttys002`


---

## ttyslot

legacy function that returns the index of the curent user's entry in some file. ttyslot() returns the index of the controlling terminal of the calling process in the file /etc/ttys, and that is (usually) the same as the index of the entry for the current user in the file /etc/utmp. BSD still has the /etc/ttys file, but System V-like systems do not. On those system it returns the current user's index in the user accounting database.

---

## ioctl

`int ioctl(int fildes, unsigned long request, ...)`

manipulates the underlying device parameters of special files. In particular, many operating characteristics of character special files (e.g. terminals) may be controlled with ioctl() request. The argument fildes must be an open file descriptor.

an ioctl request has encoded in ti whether the argument is an "in" parameter or "out" parameter, and the size of the argument, and the size of the argument argp in bytes. 

---

## getenv

`char *getenv(const char *name)`  

function obtains the current value of teh environment variable, name. The application should not modify the string pointer to the getenv() function.


---

## tcsetattr

`int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)`

function to set the termios structure.
___

## tcgetattr

`int tcgetattr(int fildes, struct termios *termios_p)
function to set the termios structure.

```c
struct termios
{
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t	c_cc[NCCS];
	speed_t	c_ispeed;
	speed_t	c_ospeed;
}
```

you can flip the bits of a flag using the bitwise NOT operator `~`
---

## tgetent

`int tgetent(char *bp, const char *name);`

routine load the entry for name. It returns 1 on succes, 0 if there is no such entry, and -1 if the terminfo database could not be found

---

## tgetflag

`int tgetflag(char *id)`

routine gets the boolean entry fo id, or zero if it is not available
___

## tgetnum

`int tgetnum(char *id)`

routine gets the numeric entry for id, or -1 if it is not available.

___

## tgetstr

`char *tgetstr(char *id, char **area)`

routine returns the string entry for id, or zero if it is not available. Use tputs to output the returned sting. The return value will also be copied to the buffer pointer to by area, and the area value will be updated to point past the null ending this value.

___

## tgoto

`char *tgoto(const char *cap, int col, int row)`

routine instantias the parameter into the given capability. The output from this routine is to be passed to tputs.

___

## tputs

`int tputs(const char *str, int affcnt, int (*putc)(int));`

routine is described on the curs_terminfo manual page. It can retrieve capabilites by eitehr termcap or termifo name.
___



# Built-in functions of bash

* **echo** : with option -n  
	it will print out the arguments after the echo command (remember it will ignore multiple white spaces)
	the -n flag will remove the newline at the end  
	return 0 unless a write error occurs
* **cd** : only relative or absolute path and no options  
	change the current active directory  
	cases:  
	`cd -` will replace the - with the old pwd in the environment variable (not mandatory) 
	when bash starts it will have OLDPWD with no value but the value changes to the old directory when you change directory. if OLDPWD doesn't exist due to unset for example or has no value set, it will complain `bash: cd: OLDPWD not set`  
	it will take the first argument and ignores the rest  
	will return a 0 if succesfull or a non-zero if it fails.  
* **pwd** : no options  
	print the absolute pathname of the current working directory. will ignore all arguments even when given.  
	return 0 when succesfull.
	on slack on this issue apparently I have to read from the env variable PWD. Because if you delete the directory while inside the directory getcwd() will return NULL. But if you unset it will still get the right directory so I can image it is using both PWD and getcwd().
* **export**: no options
	it will add an variable to the environmental variables. If no arguments given than it will display all the variables even those without a value attached to it. When bash starts it will add an extra variable called OLDPWD that is empty and changes whenever the working directory changes.  
	export will still export when the variable has not value assigned to it.  
	the names have to be a valid identifier: a-z, A-Z, 0-9 and _ underscore.
	it can export multiple variables. it will export all the valid ones. 
* **unset**: no options  
	will remove a environmental variable if not found it will do nothing. If it doesn't find it it will do nothing.  
	remember not to delete the "?" variable because that is reserved for the exit code for the last executed program.
* **env** : no options and no arguments  
	will display the environment variables of the current shell.  
	It will only display the variables that has a value assigned to it. It doesn't display it sorted. You have to make a copy of it yourself for use to be able to add and unset variables.  
	It could also be used to set variables but we don't have to do it  
* **exit** : no options
	it will exit the shell. if no exit code has been provided it will exit with the exit code of the last executed program. else it will exit with the number provided. Remember to store the last exit code even for builtin commands. e.g if exit fails due to too many argument it will exit code 
	cases:  
	`exit a` error: numeric argument required but will exit. Code will be 255
	`exit 1 a` error : too many arguments and not exit  exit code 1
	`exit a 1` error : numeric argument required but will exit code will be 255  
	`exit 1a a` error: numeric argument required but will exit code will be 255  
	`exit -1` will exit with exit code -1  
	`exit 256` will exit with exit code 0  
	`exit 257` will exit with exit code 1  
	it seems the exit code uses the remainder operator (%) in this case exit code % 256  
	it will check if the number given is a numeric argument and it doesn't use atoi()  
