/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:20:32 by romachad          #+#    #+#             */
/*   Updated: 2023/07/16 08:25:24 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_var.ctrl_c != 1 && g_var.here_doc != 1)
	{
		g_var.rcode = 130;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_var.ctrl_c != 1 && g_var.here_doc == 1)
	{
		g_var.ctrl_c = 1;
		close(STDIN_FILENO);
		ft_printf("\n");
	}
	else
	{
		g_var.rcode = 130;
		ft_printf("\n");
	}
}

void	sigquit_parent(int sig)
{
	(void)sig;
	//ft_printf("Hola, usted me llamou?\n");
	//g_var.rcode = 131;
	ft_putstr_fd("Quit\n", STDERR_FILENO);
	/*int	ret;
	for (int i=g_var.qtd_cmd -1; i>= 0; i--)
	//for (int i=0; i< g_var.qtd_cmd; i++)
	{
		//ft_printf("This is your child: %d\n",g_var.pid[i]);
		ret = kill(g_var.pid[i], SIGKILL);
		//ret = kill(g_var.pid[i], SIGQUIT);
		ft_printf("kill return code: %d\n", ret);
	}*/
}
