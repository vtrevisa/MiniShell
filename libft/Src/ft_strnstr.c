/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:15:28 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/26 14:42:04 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	position;
	size_t	i[2];

	i[0] = 0;
	position = 0;
	i[1] = 0;
	if (little == NULL || little[0] == 0)
		return ((char *)big);
	while (big[i[1]] && (i[1] + i[0]) < len)
	{
		if (little[position] == big[i[1] + i[0]])
		{
			i[0]++;
			position++;
			if (little[position] == 0)
				return ((char *)&big[i[1]]);
		}
		else if (little[position] != big[i[1] + i[0]])
		{
			i[0] = 0;
			position = 0;
			i[1]++;
		}
	}
	return (NULL);
}
