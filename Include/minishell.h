/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/23 15:10:53 by vtrevisa         ###   ########.fr       */
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

typedef struct  s_data
{
	char	**paths; //get from envp at init, used in iscmd
	char	*user; //get from envp at iniv, usen on read_line
	char	*line; //get the line readed from read_line
	char	**line_splitted; //get the line splitted at lexer
	char	**cmd; //get the cmd and the args at iscmd
	int		*lexed_class; //gets each type of each string part at tokenizer
	int		*file_fds; //get the files opened fd's at lexer_utils  e 2
	int		file_fds_index; //getds the number of files at lexer
	char	**envp; //gets the entire envp content at init
	int		count_cmd; // count the nbr of cmd's in the string at lexer
	int		*fd[2]; //get piped at execute
	int		fd_in; //get the infile fd at lexer_utils_2
	int		fd_out; //get the outfile fd at lexer_utils_2
	int		count_pipe; //count the amount of pipes in the string
	int		index; // counter fo the string parts to execute cmds
	char	*cmd_path; //get the path of the bin in iscmd
}	t_data;

/*INIT*/
void	init_data(t_data *data, char **envp);

/*READ_LINE*/
char	*read_line(t_data *data);

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
#endif