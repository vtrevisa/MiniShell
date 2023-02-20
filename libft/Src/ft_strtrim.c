/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:15:50 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/26 15:02:08 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	beg;
	int	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	beg = 0;
	end = ft_strlen(s1);
	while (s1[beg] && ft_strchr(set, s1[beg]))
		beg++;
	while (s1[end - 1] && end > beg && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, beg, (end - beg)));
}
