/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:40:46 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/02 20:46:35 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	lst_new = ft_lstnew(f(lst->content));
	if (!lst_new)
		return (0);
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&lst_new, del);
			return (0);
		}
		ft_lstadd_back(&lst_new, tmp);
		lst = lst->next;
	}
	return (lst_new);
}
