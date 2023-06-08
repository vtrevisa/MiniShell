/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:07:39 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/08 17:39:54 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

///////// Funcoes do comando EXPORT /////////
static char	**add_new_var(char **envp, char *str)
{
	int		count;
	char	**copy;

	count = 0;
	while (envp[count])
		count++;
	copy = (char **)malloc((count + 2) * sizeof(envp[0]));
	if (copy == NULL)
		error_exit("new env malloc");
	ft_memcpy(copy, envp, count * sizeof(envp[0]));
	copy[count] = ft_strdup(str);
	copy[count + 1] = NULL;
	free(envp);
	return (copy);
}

static int	check_export_str(const char *str)
{
	if (!str || !*str)
		return (1);
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (!*str)
		return (2);
	if (*str != '=')
		return (1);
	return (0);
}

static int	check_exists(char **envp, char *str)
{
	int	i;
	int	eq;

	eq = 0;
	while (str[eq] != '=' && str[eq])
		eq++;
	if (!str[eq])
		return (0);
	i = -1;
	while (envp[++i])
	{
		//ft_printf("\nOK lets check if exists!\n");
		//ft_printf("envp[%i] = %s\nstr = %s\neq is: %i\n", i, envp[i], str, eq);
		if (ft_strncmp(envp[i], str, eq) == 0)
			return (eq);
		//ft_printf("If we are still here then NOPE, no MATCH! FTS\n");
	}
	return (0);
}

char	**export(char **envp, char **str, t_data *data)
{
	int		result;
	int		i;
	int		valid;
	char	*replace;

	result = 0;
	i = -1;
	while (str[++i])
	{
		valid = check_export_str(str[i]);
		//if (check_export_str(str[i]) == 1)
		if (valid == 1)
		{
			data->rcode = 1;//Ajustar no tstruct pra deixar o return code como 1!
			result = 1;
			ft_printf("export: `%s': not a valid identifier\n", str[i]);//transformar esse output em STDERR!!
		}
		else if (valid == 0)
		{
			valid = check_exists(envp, str[i]); //se ja existir chama funcao de unset
			if (valid > 0)
			{
				replace = ft_calloc(valid, str[i][0]);
				ft_strlcpy(replace, str[i], valid + 1); //antes usava o strncpy
				envp = unset(envp, replace, data);
				free(replace);
			}
			envp = add_new_var(envp, str[i]);
		}
	}
	return (envp);
	/* Isso foi feito pois parecia que o export adicionava de tras pra frente;
	   Mas na real, nao parece ter logica na forma que eh feito...
	while (--i >= 0)
	{
		if (check_export_str(str[i]) == 0)
			//se já existir:
				//chamar funcao de unset!
			envp = add_new_var(envp, str[i]);
	}
	return (envp);*/
}
///////// FIM das funcoes do comando EXPORT /////////
