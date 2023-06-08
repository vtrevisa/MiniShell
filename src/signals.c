/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:20:32 by romachad          #+#    #+#             */
/*   Updated: 2023/06/08 17:37:25 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	sigint_handler(int sig)
{
	//if there is child process, send sigint to it
		//code to send sigint to child;
	//else
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_global_var.ctrl_c = 1;
	//write(STDIN_FILENO, "\n", 1);
	//g_global_var.saved_stdin = dup(STDIN_FILENO); 
	close(STDIN_FILENO);
	print_user_dir(&g_global_var);
	rl_redisplay();
}

/*void	sigquit_handler(int sig)
{
}*/
