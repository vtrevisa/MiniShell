/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 00:08:52 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/16 00:23:32 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{	
	size_t	position;
	size_t	s_len;

	position = 0;
	s_len = ft_strlen(src);
	if (!src)
		return (0);
	if (size > s_len + 1)
		size = s_len + 1;
	while ((position + 1) < size && src[position])
	{
		dst[position] = src[position];
		position++;
	}
	while (position < size)
	{
		dst[position] = 0;
		position++;
	}
	if (size == 0)
		dst[ft_strlen(dst)] = 0;
	return (s_len);
}
