/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/17 15:25:32 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT_CODE 1

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
	char	**paths;
	char	*user;
	char	*line;
	char	**line_splitted;
	char	**cmd;
	int		*lexed_class;
	int		*file_fds;
	int		file_fds_index;
	char	**envp;
	int		
	int		fd[2];
}	t_data;

/*INIT*/
void	init_data(t_data *data, char **envp);

/*READ_LINE*/
char	*read_line(t_data *data);

/*LEXER_UTILS*/
int	iscmd(t_data *data, char *line_splitted);
int	isarg(t_data *data, char *line_splitted);
int	issimble(t_data *data, char *line_splitted);

/*LEXER_UTILS_2*/
char	*space_to_nonprint(char *str);
int	count_splitted(t_data *data);
int	openfiles(t_data *data);

/*LEXER*/
void	lexer(t_data *data);

/*EXEC*/
int	execute(t_data *data);
#endif