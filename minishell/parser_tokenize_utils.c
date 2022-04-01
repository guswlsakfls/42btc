/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:44:56 by dha               #+#    #+#             */
/*   Updated: 2022/04/01 18:27:19 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbol(char *cmd)
{
	if (!ft_strncmp("<<", cmd, 0) || !ft_strncmp(">>", cmd, 0))
		return (2);
	if (*cmd == '|' || *cmd == '<' || *cmd == '>')
		return (1);
	return (0);
}

int	token_type(char *cmd)
{
	if (!ft_strncmp("<<", cmd, 0))
		return (HEREDOC);
	if (!ft_strncmp(">>", cmd, 0))
		return (APPEND);
	if (*cmd == '<')
		return (IREDIR);
	if (*cmd == '>')
		return (OREDIR);
	if (*cmd == '|')
		return (PIPE);
	return (CMD);
}
