/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:16:30 by romachad          #+#    #+#             */
/*   Updated: 2023/03/12 14:22:21 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	sigint_handler(int sig)//, char **envp)
{
	//If there is child process, send sigint to it
		//code to send sigint to child;
	//else:
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	print_user_dir(global_var.local_envp);
	rl_redisplay();
}
