/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:44:56 by dha               #+#    #+#             */
/*   Updated: 2022/03/10 17:56:33 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbol(char *cmd)
{
	if (!strncmp("<<", cmd, 2) || !strncmp(">>", cmd, 2))
		return (2);
	if (*cmd == '|' || *cmd == '<' || *cmd == '>')
		return (1);
	return (0);
}

int	token_type(char *cmd)
{
	if (*cmd == '\'')
		return (SQUOTE);
	else if (*cmd == '\"')
		return (DQUOTE);
	else if (*cmd == '<' || *cmd == '>')
		return (REDIR);
	else if (*cmd == '|')
		return (PIPE);
	else
		return (STR);
}
