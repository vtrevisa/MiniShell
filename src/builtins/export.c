/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:00:20 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/06/21 10:44:14 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

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
		if (ft_strncmp(envp[i], str, eq) == 0)
			return (eq);
	}
	return (0);
}

static void	if_valid(char ***envp, char *str, t_data *data, int valid)
{
	char	*replace;

	valid = check_exists(*envp, str);
	if (valid > 0)
	{
		replace = ft_calloc(valid, str[0]);
		ft_strlcpy(replace, str, valid + 1);
		*envp = unset(*envp, replace, data);
		free(replace);
	}
	*envp = add_new_var(*envp, str);
}

char	**export(char **envp, char **str, t_data *data)
{
	int		result;
	int		i;
	int		valid;

	result = 0;
	i = -1;
	while (str[++i])
	{
		valid = check_export_str(str[i]);
		if (valid == 1)
		{
			data->rcode = 1;
			result = 1;
			ft_printf("export: `%s': not a valid identifier\n", str[i]);
		}
		else if (valid == 0)
			if_valid(&envp, str[i], data, valid);
	}
	return (envp);
}
