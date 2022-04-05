/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:44:56 by dha               #+#    #+#             */
/*   Updated: 2022/04/03 14:14:19 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbol(char *cmd)
{
	if (!ft_strncmp("<<", cmd, 2) || !ft_strncmp(">>", cmd, 2))
		return (2);
	if (*cmd == '|' || *cmd == '<' || *cmd == '>')
		return (1);
	return (0);
}

int	token_type(char *cmd)
{
	if (!ft_strncmp("<<", cmd, 2))
		return (HEREDOC);
	if (!ft_strncmp(">>", cmd, 2))
		return (APPEND);
	if (*cmd == '<')
		return (IREDIR);
	if (*cmd == '>')
		return (OREDIR);
	if (*cmd == '|')
		return (PIPE);
	return (CMD);
}
