/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:33:25 by vitor             #+#    #+#             */
/*   Updated: 2022/08/18 13:36:51 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/libft.h"

int	conversions(char c, va_list ap)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret += handlechar (ap, 1);
	else if (c == 's')
		ret += handlestr (ap, 1);
	else if (c == 'p')
		ret += handlepointer (ap, 1, 2);
	else if (c == 'd' || c == 'i')
		ret += handleints(ap, 1);
	else if (c == 'u')
		ret += handleunsigned(ap, 1);
	else if (c == 'x')
		ret += handlehex(ap, 1, 1);
	else if (c == 'X')
		ret += handlehex(ap, 1, 0);
	else if (c == '%')
		ret += write(1, &c, 1);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		position;
	int		ret;

	va_start(ap, str);
	position = 0;
	ret = 0;
	while (str[position])
	{
		if (str[position] == '%')
		{
			if (ft_strchr("cspdiuxX%", str[position + 1]))
				ret += conversions(str[++position], ap);
			else
				ret += write (1, &str[position], 1);
		}
		else
			ret += write(1, &str[position], 1);
		position++;
	}
	va_end(ap);
	return (ret);
}
