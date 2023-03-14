/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/14 16:57:33 by vtrevisa         ###   ########.fr       */
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
/* 	char	*parsed; */
	int		*parsed_class;
	int		*file_fds;
	int		file_fds_index;
}	t_data;

/*INIT*/
void	init_data(t_data *data, char **envp);

/*READ_LINE*/
char	*read_line(t_data *data);

/*PARSER*/
void	parser(t_data *data);
#endif