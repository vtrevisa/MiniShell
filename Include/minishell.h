/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/11 19:22:16 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../Libft/Include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct  s_data
{
    char *line;
    char **paths;
    char **cmd;
    char	**local_envp;
	//char	*rline; //to be freed after readline();
    int	linetyped; //bool to check if something was typed.
    
}   t_data;

extern t_data	global_var;

void	sigint_handler(int sig);
void	print_user_dir(char **envp);

# define EXIT_CODE 1
#endif
