/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:16:08 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/26 14:48:19 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l_s;
	size_t	l_str;

	if (!s)
		return (0);
	l_s = ft_strlen(s);
	if (start > l_s)
	{	
		l_str = 1;
		start = l_s;
	}
	else if (len > l_s)
		l_str = l_s + 1;
	else if (start + len > l_s)
		l_str = (len - start) + 1;
	else
	{	
		l_str = len + 1;
	}
	str = malloc (l_str);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, l_str);
	return (str);
}
