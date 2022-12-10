#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#define EXEC 1
#define LIST 2

#define MAXARGS 20
#define BUFSIZE 120

#define BUILTIN_FAIL 2

extern char **environ;

/**
 * struct builtins - shell builtins
 * @builtin: builtin name
 * @f: function pointer
 *
 * Description: struct that relates a builtin and its corresponding
 * function
 *
 */
typedef struct builtins
{
	char *builtin;
	void (*f)(char **);
} builtin_t;

/**
 * struct list_s - single linked list
 * @n: number descriptor
 * @str: string
 * @next: pointer to the next node
 *
 */
typedef struct list_s
{
	int n;
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct path_node - single linked list
 * @dir: directory's absoulte path
 * @next: pointer to the next directory
 *
 * Description: linked list of the directories in the PATH
 *
 */
typedef struct path_node
{
	char *dir;
	struct path_node *next;
} path_t;

/**
 * struct cmd - command node
 * @type: command type (EXEC, LIST, etc)
 *
 * Description: command node that stores the command type
 *
 */
struct cmd
{
	int type;
};

/**
 * struct execcmd - exec command node
 * @type: EXEC
 * @argv: array of arguments
 *
 * Description: command node that stores the EXEC command type and
 * the array of strings containing the arguments to be excecuted
 *
 */
struct execcmd
{
	int type;
	char *argv[MAXARGS];
};

/**
 * struct listcmd - list command node
 * @type: LIST
 * @left: exec command node
 * @right: exec command node
 *
 * Description: command node that stores the LIST command type and
 * the pointers to the command trees that will be excecuted one
 * after the other
 *
 */
struct listcmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

void runcmd(struct cmd  *) __attribute__((noreturn));

/* command getters */
int getcmd(char **line);
ssize_t _getline(char **lineptr, size_t *n);
int reallocate_line(char **lineptr, size_t pos, size_t *n);
int gettoken(char **ps, char *es, char **q);

/* helpers */
pid_t forking(void);
void handle_sigint(int sig_num);

/* parser functions */
struct cmd *parsecmd(char *line);
struct cmd *parseexec(char **ps, char *es);
struct cmd *parseline(char **ps, char *es);

/* constructors */
struct cmd *execcmd(void);
struct cmd *listcmd(struct cmd *left, struct cmd *right);

/* finders */
char *cmdfinder(char *command);
int isabuiltin(char *line);
int peek(char **ps, char *es, char *tokens);

/* free functions */
void free_tree(struct cmd *cmd);
void safe_free(char **str);

/* builtins */
void bin_exit(char **ps);
void bin_env(char **ps);
void bin_setenv(char **ps);
void bin_setenv(char **ps);
void bin_unsetenv(char **ps);
void bin_cd(char **ps);

#endif
