/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:40:22 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/02/15 21:42:42 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

long int	ft_atoli(const char *str)
{
	int			index;
	int			if_neg;
	long int	result;

	index = 0;
	if_neg = 1;
	result = 0;
	while ((str[index] >= '\t' && str[index] <= '\r') || (str[index] == ' '))
	{
		index++;
	}
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
		{
			if_neg *= -1;
		}
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		result = (result * 10) + (str[index] - '0');
		index++;
	}
	return (result * if_neg);
}
