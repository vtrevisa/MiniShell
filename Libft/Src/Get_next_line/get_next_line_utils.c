/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:03:17 by vitor             #+#    #+#             */
/*   Updated: 2023/02/17 12:37:48 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

size_t	gn_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return ((size_t)len);
}

char	*gn_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	char	*str1;
	int		all_len;

	if (!s1)
	{
		s1 = malloc (1);
		s1[0] = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	s1_len = -1;
	s2_len = 0;
	all_len = ft_strlen (s1) + ft_strlen (s2) + 1;
	str1 = malloc(all_len);
	if (!str1)
		return (NULL);
	while (s1[++s1_len])
		str1[s1_len] = s1[s1_len];
	while (s2[s2_len])
		str1[s1_len++] = s2[s2_len++];
	str1[s1_len] = '\0';
	free(s1);
	return (str1);
}

char	*gn_strchr(char *s, int c)
{
	int	position;

	if (!s)
		return (0);
	position = 0;
	while (s[position])
	{	
		if (s[position] == (char)c)
			return ((char *)s + position);
		position++;
	}
	if (s[position] == c)
		return ((char *)s + position);
	if (c == 0)
		return (0);
	return (NULL);
}
