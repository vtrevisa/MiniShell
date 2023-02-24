# MiniShell

## GUIDE OF FUNCTIONS

| FUNCTION NAME | FUNCTION PROTOTPE | DESCRIPTION |
| ------------- | ----------------- | ----------- |
| readline | char *readline(const char *prompt); | Readline will read a line from the terminal and return it, using prompt as a prompt. Readline returns the text of the line read.  A blank line returns the empty string. |
| rl_clear_history | void rl_clear_history (void); | Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.
| rl_on_new_line |	int rl_on_new_line (void); | Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. |
| rl_replace_line	|	void rl_replace_line (const char *text, int clear_undo); | Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. |
| rl_redisplay | void rl_redisplay (void); | Change what’s displayed on the screen to reflect the current contents of rl_line_buffer. |
| add_history | void add_history (char *string) | Place string at the end of the history list. The associated data field (if any) is set to NULL. |
| printf | | |
| malloc | | |
| free | | |
| write | | |
| access | int access(const char *pathname, int mode); | Access command is used to check whether the calling program has access to a specified file. It can be used to check whether a file exists or not.  |
| open | | |
| read | | |
| close | | |
| fork | pid_t fork(void); | Fork() creates a new process by duplicating the calling process. |
| wait | pid_t wait(int *wstatus); | The  wait()  system call suspends execution of the calling thread until one of its children terminates.  The call wait(&wstatus) is equivalent to: waitpid(-1, &wstatus, 0); |
| waitpid | pid_t waitpid(pid_t pid, int *wstatus, int options); | The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed  state. |
| wait3 | pid_t wait3(int *wstatus, int options, struct rusage *rusage); | The  wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage. |
| wait4 | pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage); | The  wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage. |
| signal | sighandler_t signal(int signum, sighandler_t handler); | Signal() sets the disposition of the signal signum to handler, which is either SIG_IGN, SIG_DFL, or the address of a programmer-de‐qfined function (a "signal handler"). |
| sigaction | int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); | The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.  (See signal(7) for an overview of signals.) |
| sigemptyset | int sigemptyset(sigset_t *set); | sigemptyset() initializes the signal set given by set to empty, with all signals excluded from the set. |
| sigaddset | int sigaddset(sigset_t *set, int signum); | sigaddset() add signal signum from set. |
| kill | int kill(pid_t pid, int sig); | The kill() system call can be used to send any signal to any process group or process. |
| getcwd | char *getcwd(char *buf, size_t size); | The getcwd() function copies an absolute pathname of the current working directory to the array pointed to  by  buf,  which  is  of length size. |
| chdir | int chdir(const char *path); | chdir() changes the current working directory of the calling process to the directory specified in path. |
| stat | int stat(const char *pathname, struct stat *statbuf); | stat() retrieves information about the file pointed to by pathname. |
| lstat | int lstat(const char *pathname, struct stat *statbuf); | lstat()  is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that the link refers to. |
| fstat | int fstat(int fd, struct stat *statbuf); | fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd. |
| unlink | int unlink(const char *pathname); | unlink()  deletes  a  name  from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse. |
| execve | | |
| dup | int dup(int oldfd); | The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new de‐scriptor. |
| dup2 | int dup2(int oldfd, int newfd); | The  dup2()  system  call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd.  If the file descriptor newfd was previously open, it is silently closed before  being reused. |
| pipe | | |
| opendir | DIR *opendir(const char *name); | The opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory. |
| readdir | struct dirent *readdir(DIR *dirp); | The  readdir()  function  returns  a  pointer  to  a dirent structure representing the next directory entry in the directory stream pointed to by dirp. It returns NULL on reaching the end of the directory stream or if an error occurred. (STRUCT AT THE END) |
| closedir | int closedir(DIR *dirp); | The closedir() function closes the directory stream associated with dirp.  A successful call to closedir() also closes the underlying file descriptor associated with dirp.  The directory stream descriptor dirp is not available after this call. |
| strerror | char *strerror(int errnum); | The  strerror()  function returns a pointer to a string that describes the error code passed in the argument errnum, possibly using the LC_MESSAGES part of the current locale to select the appropriate language. |
| perror | void perror(const char *s); | The  perror()  function produces a message on standard error describing the last error encountered during a call to a system or library function. |
| isatty | int isatty(int fd); | The isatty() function tests whether fd is an open file descriptor referring to a terminal. |
| ttyname | char *ttyname(int fd); | The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error. |
| ttyslot | int ttyslot(void); | The function ttyslot() returns the index of the controlling terminal of the calling process in the file /etc/ttys, and that is (usually) the same as the index of the entry for the current user in the file /etc/utmp.|
| ioctl | int ioctl(int fd, unsigned long request, ...); | The  ioctl() system call manipulates the underlying device parameters of special files. |
| getenv | char *getenv(const char *name); | The getenv() function searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string. |
| tcsetattr | int tcsetattr(int fd, int optional_actions, const struct termios *termios_p); | tcsetattr()  sets  the parameters associated with the terminal (unless support is required from the underlying hardware that is not available) from the termios structure referred to by termios_p. |
| tcgetattr | int tcgetattr(int fd, struct termios *termios_p); | tcgetattr()  gets  the  parameters associated with the object referred by fd and stores them in the termios structure referenced by termios_p. |
| tgetent | int tgetent(char *bp, const char *name); | The tgetent routine loads the entry for name. It returns 1 on success, 0 if there is no such entry, and -1 if the terminfo database could not be found. The emulation ignores the buffer pointer bp. |
| tgetflag | int tgetflag(char *id); | The tgetflag routine gets the boolean entry for id, or zero if it is not available. |
| tgetnum | int tgetnum(char *id); | The tgetnum routine gets the numeric entry for id, or -1 if it is not available. |
| tgetstr | char *tgetstr(char *id, char **area); | The tgetstr routine returns the string entry for id, or zero if it is not available. Use tputs to output the returned string. The return value will also be copied to the buffer pointed to by area, and the area value will be updated to point past the null ending this value. |
| tgoto | char *tgoto(const char *cap, int col, int row); | The tgoto routine instantiates the parameters into the given capability. The output from this routine is to be passed to tputs. |
| tputs | int tputs(const char *str, int affcnt, int (*putc)(int)); | The tputs routine is described on the curs_terminfo(3X) manual page. It can retrieve capabilities by either termcap or terminfo name. |

READDIR STRUCT
```
struct dirent {
               ino_t          d_ino;       /* Inode number */
               off_t          d_off;       /* Not an offset; see below */
               unsigned short d_reclen;    /* Length of this record */
               unsigned char  d_type;      /* Type of file; not supported
                                              by all filesystem types */
               char           d_name[256]; /* Null-terminated filename */
           };
```
