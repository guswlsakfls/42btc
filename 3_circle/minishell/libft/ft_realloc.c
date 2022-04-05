/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:43:00 by dha               #+#    #+#             */
/*   Updated: 2022/03/29 19:45:03 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, int pre_size, int new_size)
{
	void	*new_ptr;
	int		cp_size;

	if (pre_size < new_size)
		cp_size = pre_size;
	else
		cp_size = new_size;
	new_ptr = ft_malloc(sizeof(char), new_size);
	ft_memmove(new_ptr, ptr, cp_size);
	free(ptr);
	return (new_ptr);
}
