/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitor <vitor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:01:49 by vitor             #+#    #+#             */
/*   Updated: 2022/06/23 23:02:36 by vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*nlst;

	tmp = NULL;
	nlst = NULL;
	if (!lst || !(*f) || !(*del))
		return (NULL);
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_lstclear (&tmp, del);
			return (NULL);
		}
		else
			ft_lstadd_back (&nlst, tmp);
		lst = lst->next;
	}
	return (nlst);
}
