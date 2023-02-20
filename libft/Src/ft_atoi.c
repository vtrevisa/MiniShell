/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 01:02:47 by vtrevisa          #+#    #+#             */
/*   Updated: 2022/06/14 01:00:26 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	if_neg;
	int	result;

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
