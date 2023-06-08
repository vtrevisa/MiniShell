/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:03:17 by vitor             #+#    #+#             */
/*   Updated: 2022/08/18 13:40:02 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

char	*get_next_line(int fd);

char	*ft_strfjoin(char *s1, char *s2)
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
