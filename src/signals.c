/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:20:32 by romachad          #+#    #+#             */
/*   Updated: 2023/06/04 21:06:18 by vtrevisa         ###   ########.fr       */
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
	print_user_dir(&global_var);
	rl_redisplay();
}

/*void	sigquit_handler(int sig)
{
}*/
