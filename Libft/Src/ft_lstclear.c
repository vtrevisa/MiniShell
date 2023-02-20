/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:05:33 by vitor             #+#    #+#             */
/*   Updated: 2022/06/23 23:05:55 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{	
	t_list	*temp;
	t_list	*elem;

	if (!(*lst))
		return ;
	elem = *lst;
	while (elem)
	{
		temp = elem->next;
		ft_lstdelone(elem, del);
		elem = temp;
	}
	*lst = NULL;
}
