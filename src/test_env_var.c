/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:49:25 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/05/08 16:55:50 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*reveal_var(char **envp, char *str, int var_size)
{
	char	*str;
	char	*tmp;

	tmp = ft_strncpy
	/* while (!ft_strnstr(envp[index], "PATH=", 5))
		index++;
	
	return (envp[index] + 5); */
	ft_printf("\nstr=%s\nvar_size=%d\n", str, var_size);
}

int main(char **envp)
{
	int		index1 = 0;
	char	str1[] = "What is the word? R: $WORD";
	int		var_size = 0;
	char	*str;
	int		flag = 1;

	while (str1[index1 + var_size] != '\0' && flag == 1)
	{
		ft_printf("%c", str1[index1 + var_size]);
		if (str1[index1 + var_size] == '$')
		{
			while (str1[index1 + var_size] != ' ' && str1[index1 + var_size] != '\0')
			{
				var_size++;
				flag = 2;
			}
			str = reveal_var(envp, str1+index1, var_size);
		}
		if (flag == 1)
			index1++;
	}
	/* ft_printf("%s\n", str); */
}