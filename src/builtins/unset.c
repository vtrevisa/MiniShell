/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:01:15 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/07/05 11:23:02 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	check_unset_str(const char *str)
{
	if (!str || !*str)
		return (1);
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	str++;
	while (ft_isalnum(*str) || *str == '_')
		str++;
	if (*str == '=')
		return (1);
	return (0);
}

static void	if_invalid(const char *str, t_data *data)
{
	if (check_unset_str(str))
	{
		data->rcode = 1;
		ft_printf("unset: `%s': not a valid identifier\n", str);
	}
}

static int	set_i_to_remove(int *count, const char *str, char **envpl, int *i_to_remove)
{
	while (envpl[++*count])
	{
		if (ft_strncmp(envpl[*count], str, strlen(str)) == 0)
		{
			if (envpl[*count][strlen(str)] == '=')
			{
				*i_to_remove = *count;
			}
		}
	}
	return (*i_to_remove);
}

char	**unset(char **envpl, const char *str, t_data *data)
{
	int		count;
	int		i_to_remove;
	char	**copy;

	i_to_remove = -1;
	count = -1;
	if_invalid(str, data);
	i_to_remove = set_i_to_remove(&count, str, envpl, &i_to_remove);
	if (i_to_remove == -1)
		return (envpl);
	copy = (char **)malloc((count) * sizeof(envpl[0]));
	ft_memset(copy, 0, count * sizeof(envpl[0]));
	if (copy == NULL)
		error_exit("unset env malloc");
	if (count == 1)
		copy[0] = NULL;
	else
	{
		ft_memcpy(copy, envpl, i_to_remove * sizeof(envpl[0]));
		ft_memcpy(copy + i_to_remove, envpl + i_to_remove + 1, \
	(count - i_to_remove - 1) * sizeof(envpl[0]));
	}
	free(envpl[i_to_remove]);
	free(envpl);
	return (copy);
}

char	**prep_unset(char **envpl, const char **str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i])
		envpl = unset(envpl, str[i], data);
	return (envpl);
}
