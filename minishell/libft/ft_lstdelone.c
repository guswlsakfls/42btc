/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:16:36 by dha               #+#    #+#             */
/*   Updated: 2022/03/16 16:21:27 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == 0)
		return ;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (del)
		del(lst -> content);
	free(lst);
}
