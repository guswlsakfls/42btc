/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyze_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:29:38 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/26 20:35:00 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err_msg(int type)
{
	char *const	err_msg[5] = {"`|'", "`<'", "`>'", "`<<'", "`>>'"};
	int			i;

	ft_putstr_fd(ERR_PRPT, 2);
	ft_putstr_fd(ERR_SYX, 2);
	if (type == 0)
	{
		ft_putstr_fd("'newline'\n", 2);
		return ;
	}
	i = 0;
	while (i < 5)
	{
		if (type == 1 << i)
			break ;
		i++;
	}
	ft_putendl_fd(err_msg[i - 1], 2);
}

static void	free_token_str(void *token)
{
	free(((t_token *)token)->str);
}

void	clear_tokens(t_list **tokens)
{
	ft_lstiter(*tokens, free_token_str);
	ft_lstclear(tokens, free);
	*tokens = NULL;
}
