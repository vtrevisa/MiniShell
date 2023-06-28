/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:20:32 by romachad          #+#    #+#             */
/*   Updated: 2023/06/28 12:12:45 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	sigint_handler(int sig)
{
	if (g_var.ctrl_c != 1)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_var.here_doc == 1)
		{
			g_var.ctrl_c = 1;
			g_var.saved_stdin = dup(STDIN_FILENO);
			close(STDIN_FILENO);
		}
		print_user_dir(&g_var);
		rl_redisplay();
	}
	else
		ft_printf("\n");
}
