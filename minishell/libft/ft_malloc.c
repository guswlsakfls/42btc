/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 18:24:30 by dha               #+#    #+#             */
/*   Updated: 2022/03/18 21:28:31 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(size_t size, size_t cnt)
{
	void	*ptr;

	ptr = malloc(size * cnt);
	if (!ptr)
		ft_error_exit("Error\n Memory allocation failed");
	ft_bzero(ptr, size * cnt);
	return (ptr);
}
