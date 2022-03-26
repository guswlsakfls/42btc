/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:40:31 by dha               #+#    #+#             */
/*   Updated: 2022/03/26 20:49:51 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_copy_envs(t_list *envs)
{
	t_list	*cp;
	t_env	*env;

	cp = NULL;
	while (envs)
	{
		env = (t_env *)ft_malloc(sizeof(t_env), 1);
		env->key = ((t_env *)envs->content)->key;
		env->value = ((t_env *)envs->content)->value;
		ft_lstadd_back(&cp, ft_lstnew(env));
		envs = envs->next;
	}
	return (cp);
}

void	swap_env(t_env *prev, t_env *curr)
{
	t_env	tmp;

	tmp.key = prev->key;
	tmp.value = prev->value;
	prev->key = curr->key;
	prev->value = curr->value;
	curr->key = tmp.key;
	curr->value = tmp.value;
}

t_list	*get_sorted_envs(t_list *envs)
{
	t_list	*cp;
	t_list	*tmp;
	t_list	*ptr;
	t_list	*prev_ptr;

	cp = get_copy_envs(envs);
	tmp = cp;
	while (tmp->next)
	{
		ptr = ft_lstlast(tmp);
		prev_ptr = ptr->prev;
		while (prev_ptr)
		{
			if (ft_strncmp(((t_env *)prev_ptr->content)->key, \
				((t_env *)ptr->content)->key, 0) > 0)
				swap_env(prev_ptr->content, ptr->content);
			ptr = ptr->prev;
			prev_ptr = prev_ptr->prev;
		}
		tmp = tmp->next;
	}
	return (cp);
}

int	export_no_arg(t_list *envs)
{
	t_list	*sorted_envs;
	t_list	*ptr;

	sorted_envs = get_sorted_envs(envs);
	ptr = sorted_envs;
	while (ptr)
	{
		if (strncmp(((t_env *)ptr->content)->key, "?", 2) == 0)
		{
			ptr = ptr->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_env *)ptr->content)->key, 1);
		if (((t_env *)ptr->content)->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_env *)ptr->content)->value, 1);
			ft_putendl_fd("\"", 1);
		}
		ptr = ptr->next;
	}
	ft_lstclear(&sorted_envs, free);
	return (0);
}
