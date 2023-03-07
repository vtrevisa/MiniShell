/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:21:06 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/03/06 20:35:10 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/Include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct  s_data
{
    char *line;
    char **paths;
    char **cmd;
	//char	*rline; //to be freed after readline();
    int	linetyped; //bool to check if something was typed.
    
}   t_data;

#ifndef MINISHELL_H
# define MINISHELL_H
# define EXIT_CODE 1
#endif
