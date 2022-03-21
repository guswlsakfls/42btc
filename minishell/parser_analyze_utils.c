/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyze_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:29:38 by hyunjinjo         #+#    #+#             */
/*   Updated: 2022/03/20 22:32:57 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_token_str(void *token)
{
    free(((t_token *)token)->str);
}

void tokens_clear(t_list **tokens)
{
    ft_lstiter(*tokens, free_token_str);
    ft_lstclear(tokens, free);
}