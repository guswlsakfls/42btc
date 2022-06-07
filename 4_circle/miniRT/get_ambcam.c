/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambcam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:36:58 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:36:58 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

void	get_amb(t_info *info)
{
	t_amb	*new;

	if(info->qtys[0] != 0)
		exit(1);
	new = malloc(sizeof(t_amb));
	if (!new)
		exit(1);
	ft_bzero(new, 0);
	info_line_split(info, 0);
	new->ratio = get_ratio(info->split[1]);
	new->color = get_color(info->split[2]);
	info->amb = new;
	info->qtys[0] += 1;
}

void		lst_add_back_cam(t_camera **lst, t_camera *new)
{
	t_camera	*temp;

	temp = (*lst);
	if (!new)
		return ;
	if (!*lst)
		(*lst) = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

void	get_camera(t_info *info)
{
	t_camera	*new;

	new = malloc(sizeof(t_camera));
	if (!new)
		exit(1);
	ft_bzero(new, 0);
	info_line_split(info, 1);
	new->coordi_view = get_vector(info->split[1]);
	new->normalize = get_vector(info->split[2]);
	new->fov = get_double(info->split[3]);
	new->next = NULL;
	new->prev = NULL;
	lst_add_back_cam(&info->camera, new);
	info->qtys[1] += 1;
}
