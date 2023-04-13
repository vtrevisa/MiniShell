/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrevisa <vtrevisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:07:57 by vtrevisa          #+#    #+#             */
/*   Updated: 2023/04/13 17:13:29 by vtrevisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int main(void)
{
    char *str = ft_strnstr("exit", "\n", 4);
    char *s = "\n";
    if (ft_strnstr("exit", s, 4) != 0)
        ft_printf("%s\n", str);
}