/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romachad <romachad@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:16:30 by romachad          #+#    #+#             */
/*   Updated: 2023/03/11 19:35:16 by romachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	sigint_handler(int sig)//, char **envp)
{
	//printf("\nSigint rx\n");
	printf("\n");
	print_user_dir(global_var.local_envp);
}
