/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/08 17:40:14 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT_CODE 1
# define FILE_STDIN 4
# define FILE_STDIN_CONC 5
# define FILE_STDOUT 6
# define FILE_STDOUT_CONC 7
# define PIPE 8

# include "../Libft/Include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>

/*Structs and ENUM for PARSER*/
typedef enum s_ state
{
	NORMAL,
	ESPACE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	VARIABLE,
	VARIABLE_IN_DQ,
}	t_state;

typedef struct s_parser
{
	int		i;
	int		j;
	int		index;
	int		index2;
	int		redir_type;
	char	*str;
	t_state	st;
}	t_parser;

typedef struct s_data
{
	/*PROMPT_LOOP*/
	char	*line; //get the line readed from read_line
	char	linetyped; //bool to check if someting was typed
	/*PARSER*/
	//char	**cmds; //get the line splitted
	char	*tmp;
	/*LEXER*/
	char	**line_splitted; //get the line splitted
	int		file_fds_index; //getds the number of files issimble
	int		*file_fds; //get the files opened fd's at lexer_utils  e 2
	int		count_cmd; // count the nbr of cmd's in the string at lexer
	int		count_pipe; //count the amount of pipes in the string
	char	*cmd_path; //get the path of the bin in iscmd
	/*TOLKENIZER*/
	int		*lexed_class; //gets each type of each string part
	char	**paths; //get from envp at init, used in iscmd
	char	**cmd; //get the cmd and the args at iscmd
	/*PRINT_USER_DIR*/
	char	*user; //get from envp at init, used on read_line
	/*EXEC*/
	char	**envp; //gets the entire envp content at init
	int		fd[2]; //get piped at execute
	int		fd_in; //get the infile fd at lexer_utils_2
	int		fd_out; //get the outfile fd at lexer_utils_2
	int		pipes; //count the pipe creation
	/*Roger check antes de exece*/
	char	**cmd_split;
	char	***full_cmd;
	int		builtin;
	/*Return code*/
	int		rcode;
	/*Ctrl-C flag*/
	int		ctrl_c;
	/*Roger Redirect vars*/
	char	***cmd_redir;
	int		redir_error;

	/*Roger MOVED FROM PIPER*/
	int		qtd_cmd;

	/*Roger Backup STDIN STDOUT*/
	int		saved_stdin;
	int		saved_stdout;
	int		saved_stderr;
	//int	fd[2];
}	t_data;

typedef struct t_pipe
{
	char	**argv;
	//char	*cmd_str; Legacy, used only in pipex
	char	**cmd_args;
	char	*fpath;
	int		*pid;
	int		*pipes;
	int		builtin;
	int		flag;
	int		qtd_cmd;
	int		cmd_n;
	int		pipe_i;
}	t_pipe;

extern t_data	g_global_var;

/*INIT*/
void	init_data(t_data *data, char **envp);
char	**copy_double_str(char **envp); //renomear de envp para str?

/*READ_LINE*/
//char	*read_line(t_data *data);
void	*read_line(t_data *data);

/*LEXER_UTILS*/
int		iscmd(t_data *data, char *line_splitted);
int		isarg(t_data *data, char *line_splitted);
int		issimble(t_data *data, char *line_splitted);

/*LEXER_UTILS_2*/
char	*space_to_nonprint(char *str);
int		count_splitted(t_data *data);
int		openfiles(t_data *data);

/*LEXER*/
void	lexer(t_data *data);

/*EXEC*/
int		execute(t_data *data, char **args);
int		child_2(t_data *data);
int		child_3(t_data *data);
int		child_1(t_data *data);

/*BUILTINS*/
int		echo_n(char **text);
int		change_directory(char **paths, char **envp);
int		pwd(void);
void	env(char **envp);
char	**export(char **envp, char **str, t_data *data);
char	**prep_unset(char **envpl, const char **str, t_data *data);
char	**unset(char **envpl, const char *str, t_data *data);
void	error_exit(char *str);
void	exit_shell(t_data *data);

/*UTILS*/
void	free_char_array(char **array);

/*Roger EXEC*/
int		builtin_exec_main(t_data *data);
int		is_there_pipes(char *str);

/*PIPER*/
void	piper(t_data *data);

/*PIPE Functions*/
char	**treat_str(char *str);
char	*path_search(char *envp[], const char *cmd);
int		child_prog(t_pipe *args, t_data *data);
void	free_args(t_pipe *args);
void	close_pipes(t_pipe *args, t_data *data);
/*PIPE Functions for builtins*/
int		builtin_checker(char *str);
int		builtin_exec_pipe(t_pipe *args, t_data *data);

/*Roger Parser*/
void	parser(char *str, t_data *data);
char	**split_pipes(char *str);
char	**parse_redir(char **parsed, t_data *data, int index);
int		check_close_dq(char *str);
char	*find_variable(char *var, t_data *data);
void	parse_var_redir(t_data *data, t_parser *parser);
void	trim_quote_redir(t_parser *p);
char	*here_doc(char *str);
char	*parse_var_heredoc(char *str, t_data *data);

/*Signals*/
void	sigint_handler(int sig);
//void	sigquit_handler(int sig);
void	print_user_dir(t_data *data);

#endif
