/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:40:46 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/02 16:49:41 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*lst_res;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	lst_new = ft_lstnew(f(lst->content));
	if (!lst_new)
		return (0);
	lst_res = lst_new;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&lst_new, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back(&lst_new, tmp);
		lst_new = lst_new->next;
	}
	lst_new = NULL;
	return (lst_res);
}
