/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:13:43 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/26 15:04:59 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countword(const char *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (*s)
	{
		while (*s && *s == c)
		{
			if (flag == 1)
				flag = 0;
			s++;
		}
		while (*s && *s != c)
		{
			if (flag == 0)
			{
				count++;
				flag = 1;
			}
			s++;
		}
	}
	return (count);
}

static int	countstr(const char *s, char c)
{	
	int	i;

	i = 0;
	while (*s != c && *s)
	{
		s++;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{	
	int		pos1;
	char	**nstr;

	if (!s)
		return (NULL);
	pos1 = 0;
	nstr = malloc (sizeof(char *) * ((countword(s, c)) + 1));
	if (!nstr)
		return (NULL);
	while (*s)
	{	
		while (*s && *s == c)
			s++;
		while (*s && *s != c)
		{
			nstr[pos1] = malloc ((countstr(s, c)) + 1);
			if (!nstr[pos1])
				return (NULL);
			ft_strlcpy(nstr[pos1], s, (countstr(s, c)) + 1);
			s += countstr(s, c);
			pos1++;
		}
	}
	nstr[pos1] = NULL;
	return (nstr);
}
