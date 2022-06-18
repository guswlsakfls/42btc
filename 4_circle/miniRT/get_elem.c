/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:37:22 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/07 15:37:22 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./miniRT.h"

void	list_add_back_elem(t_elem *new, t_elem **lst)
{
	t_elem	*temp;

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
	}
}

void	get_light(t_elem *new, t_info *info)
{
	info_line_split(info, 2);
	new->pos = get_vector(info->split[1]);
	new->ratio = get_ratio(info->split[2]);
	new->color = get_color(info->split[3]);
	list_add_back_elem(new, &info->light);
	free_split(info->split, 4);
	info->qtys[2] += 1;
}

void	get_sphere(t_elem *new, t_info *info)
{
	info_line_split(info, 3);
	new->pos = get_vector(info->split[1]);
	new->diam = get_double(info->split[2]);
	new->color = get_color(info->split[3]);
	list_add_back_elem(new, &info->sp);
	free_split(info->split, 4);
	info->qtys[3] += 1;
}

void	get_plane(t_elem *new, t_info *info)
{
	info_line_split(info, 4);
	new->pos = get_vector(info->split[1]);
	check_normal(get_vector(info->split[2]));
	new->normal = vec_unit(get_vector(info->split[2]));
	new->color = get_color(info->split[3]);
	new->diam = -1;
	list_add_back_elem(new, &info->pl);
	free_split(info->split, 4);
	info->qtys[4] += 1;
}

void	get_cylinder(t_elem *new, t_info *info)
{
	info_line_split(info, 5);
	new->pos = get_vector(info->split[1]);
	check_normal(get_vector(info->split[2]));
	new->normal = vec_unit(get_vector(info->split[2]));
	new->diam = get_double(info->split[3]);
	new->height = get_double(info->split[4]);
	new->color = get_color(info->split[5]);
	list_add_back_elem(new, &info->cy);
	free_split(info->split, 6);
	info->qtys[4] += 1;
	cap_in_cylinder(new, info);
}
