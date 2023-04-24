/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/24 02:02:59 by romachad         ###   ########.fr       */
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

typedef struct  s_data
{

	/*PROMPT_LOOP*/
	char	*line; //get the line readed from read_line
	char	linetyped; //bool to check if someting was typed

	/*PARSER*/
	//char	**cmds; //get the line splitted

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
}	t_data;

typedef struct	p_pipe
{
	char	**argv;
	//char	*cmd_str; Legacy, used only in pipex
	char	**cmd_args;
	char	*fpath;
	int		*pid;
	int		*pipes;
	int		flag;
	int		qtd_cmd;
	int		cmd_n;
	int		pipe_i;
}	t_pipe;

/*INIT*/
void	init_data(t_data *data, char **envp);

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
int		change_directory(char *path, char **envp);
int		pwd(void);
void	env(char **envp);
char	**export(char **envp, char **str);
char	**prep_unset(char **envpl, const char **str);
char	**unset(char **envpl, const char *str);
void	error_exit(char *str);

/*UTILS*/
void	free_char_array(char **array);

/*PARSER*/
void	parser(t_data *data);

/*PIPE Functions*/
char	**treat_str(char *str);
char	*path_search(char *envp[], const char *cmd);
int		child_prog(t_pipe *args, t_data *data);
void	free_args(t_pipe *args);
void	close_pipes(t_pipe *args);

#endif
