/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:31:10 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/03 19:58:46 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_curr;
	t_list	*lst_next;

	if (lst == 0 || del == 0)
		return ;
	lst_curr = *lst;
	while (lst_curr)
	{
		lst_next = lst_curr->next;
		ft_lstdelone(lst_curr, del);
		lst_curr = lst_next;
	}
	*lst = NULL;
}
