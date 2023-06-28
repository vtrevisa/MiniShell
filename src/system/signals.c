/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:20:32 by romachad          #+#    #+#             */
/*   Updated: 2023/06/28 04:31:03 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	sigint_handler(int sig)
{
	//if there is child process, send sigint to it
		//code to send sigint to child;
	//else
	if (global_var.ctrl_c != 1)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (global_var.here_doc == 1)
		{
			global_var.ctrl_c = 1;
			global_var.saved_stdin = dup(STDIN_FILENO); 
			close(STDIN_FILENO);
		}
		print_user_dir(&global_var);
		rl_redisplay();
	}
	else
		ft_printf("\n");
}

/*void	sigquit_handler(int sig)
{
}*/
