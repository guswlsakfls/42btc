/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:41:57 by dha               #+#    #+#             */
/*   Updated: 2022/03/29 19:46:04 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strarr_clear(char ***strarr)
{
	int	idx;

	idx = 0;
	while ((*strarr)[idx])
	{
		free((*strarr)[idx]);
		idx++;
	}
	free(*strarr);
	*strarr = NULL;
	return ;
}
