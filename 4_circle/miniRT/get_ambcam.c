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

	if (info->qtys[0] != 0)
		msg_exit("Too many amblight ");
	new = malloc(sizeof(t_amb));
	if (!new)
		msg_exit("");
	ft_bzero(new, 0);
	info_line_split(info, 0);
	new->ratio = get_ratio(info->split[1]);
	new->color = get_color(info->split[2]);
	info->amb = new;
	info->qtys[0] += 1;
	free_split(info->split, 3);
}

void	lst_add_back_cam(t_camera **lst, t_camera *new)
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

static void	check_fov(double num)
{
	if (num < 0 || num > 180)
		msg_exit("fov range ");
}

void	get_camera(t_info *info)
{
	t_camera	*new;

	new = malloc(sizeof(t_camera));
	if (!new)
		msg_exit("malloc ");
	ft_bzero(new, 0);
	info_line_split(info, 1);
	new->coordi_view = get_vector(info->split[1]);
	check_normal(get_vector(info->split[2]));
	new->normalize = vec_unit(get_vector(info->split[2]));
	check_fov(get_double(info->split[3]));
	new->fov = tan((get_double(info->split[3]) * (M_PI / 180)) / 2);
	new->next = NULL;
	new->prev = NULL;
	lst_add_back_cam(&info->camera, new);
	info->qtys[1] += 1;
	free_split(info->split, 4);
}
