/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:14:54 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/14 00:49:17 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	ov_dst;
	size_t	ov_src;

	s_len = 0;
	d_len = 0;
	ov_dst = ft_strlen(dst);
	ov_src = ft_strlen((char *)src);
	d_len = ov_dst;
	if (size == 0)
		return (ov_src);
	if (size <= d_len)
		return (ov_src + size);
	while ((d_len + 1) < size && src[s_len] != '\0')
	{
		dst[d_len] = src[s_len];
		d_len++;
		s_len++;
	}
	dst[d_len] = 0;
	return (ov_dst + ov_src);
}
