/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:49:25 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/05/11 16:08:24 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static char *fill_init(char *str, int init_l)
{
	int	index = 0;
	char *ret = malloc (sizeof (char) * init_l + 1);

	while (index < init_l)
	{
		ret[index] = str[index];
		index++;
	}
	return (ret);
}

static char *fill_var (char *str, int var_l, char **envp)
{
	int	index = 0;
	char *ret;
	char *tmp = malloc (sizeof (char) * var_l + 1);
	
	
	while (index <= var_l)
	{
		tmp[index - 1] = str[index];
		index++; 
	}
/* 	ft_printf("\n------FILL VAR--\n");
	ft_printf("	Index = %d\n", index); */
	index = 0;
	while (envp[index] != NULL && !ft_strnstr(envp[index], tmp, var_l))
	{
/* 		ft_printf("TESTE ENVP = %s\n", envp[index]);
		ft_printf("Index = %d\n", index); */
		index++;
	}
	if (envp[index] == NULL)
		return (NULL);
/* 	ft_printf("	Temp=%s\n", tmp); */
	ret = ft_strdup(envp[index] + var_l + 1);
/* 	write (1, "ok\n", 3);
	ft_printf("\n------END FILL VAR--\n\n"); */
	return (ret);
}

static char *fill_end(char *str, int end_l)
{
	int	index = 0;
	char *ret = malloc (sizeof (char) * end_l + 1);

	while (index < end_l)
	{
		ret[index] = str[index];
		index++;
	}
	return (ret);
}

char *unveil_vars(char **envp, char* str)
{
	char	*init;
	char	*var;
	char	*end;
	char	*converted;
	int		index = 0;
	int		max_size = ft_strlen(str);
	int		init_l = 0;
	int		var_l = 0;
	int		end_l = 0;
	char	*ret;

	index = 0;
	
	while (index < max_size)
	{
		while (str[index] != '$' && index < max_size)
		{
			init_l++;
			index++;
		}
		if (str[index] == '$' && index < max_size)
		{
			while (ft_isalpha(str[++index]) && index < max_size)
			{
				var_l++;
			}
		}
		while (index < max_size)
		{
			index++;
			end_l++;
		}
	}
/* 	ft_printf("\n--MAIN--\n");
	ft_printf("Index=%d\n", index);
	ft_printf("Max_size=%d\n", max_size);
	ft_printf("Init_l=%d\n", init_l);
	ft_printf("Var_l=%d\n", var_l);
	ft_printf("End_l=%d\n", end_l); */
	init = fill_init(str, init_l);
/* 	ft_printf("Init=%s\n", init); */
	var = fill_var(str + init_l, var_l, envp);
	if (var == NULL)
	{
		ret = str;
		free (str);
		return (ret);
	}
	/* ft_printf("Var=%s\n", var); */
	end = fill_end(str + init_l + var_l + 1, end_l);
	/* ft_printf("End=%s\n", end); */
	ret = malloc (sizeof (char) * (index + 2));

	ft_strlcpy(ret, init, index + 1);
/* 	ft_printf("ret + init = %s\n", ret); */
	
	ft_strlcat(ret, var, index + 1);
/* 	ft_printf("ret + var = %s\n", ret); */
	
	ft_strlcat(ret, end, index + 1);
/* 	ft_printf("ret + end = %s\n", ret); */
	free (str);
	return (ret);
	}
