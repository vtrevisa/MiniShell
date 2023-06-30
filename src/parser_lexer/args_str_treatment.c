/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_str_treatment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 02:46:02 by romachad          #+#    #+#             */
/*   Updated: 2023/06/30 16:41:22 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	treat_quotes(char *str)
{
	char	c;
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	while (str[++i])
	{
		if ((str[i] == '"' && str[i - 1] != '\\' && flag == 0) \
				|| (str[i] == 39 && str[i - 1] != '\\' && flag == 0))
		{
			flag = 1;
			c = str[i];
			str[i] = 18;
		}
		if (flag == 1 && str[i] == ' ')
			str[i] = 17;
		if (flag == 1 && str[i] == c && str[i - 1] != '\\')
		{
			str[i] = 18;
				flag = 0;
		}
	}
}

static void	add_space(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 17)
				str[i][j] = ' ';
		}
	}
}

static void	change_cmd(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			str[i] = 17;
		if (str[i] == 39)
			str[i] = 18;
		if (str[i] == ' ')
			break ;
	}
}

static void	return_cmd(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 17)
			str[i] = '"';
		if (str[i] == 18)
			str[i] = 39;
	}
}

char	**treat_str(char *str)
{
	char	*t_str;
	char	**str_treated;
	char	set[2];
	int		i;

	set[0] = 18;
	set[1] = 0;
	change_cmd(str);
	treat_quotes(str);
	str_treated = ft_split(str, ' ');
	return_cmd(str_treated[0]);
	i = -1;
	while (str_treated[++i])
	{
		t_str = ft_strtrim(str_treated[i], set);
		if (t_str[0] == 0)
			free(t_str);
		else
		{
			free(str_treated[i]);
			str_treated[i] = t_str;
		}
	}
	add_space(str_treated);
	return (str_treated);
}
