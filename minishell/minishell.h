/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/09 14:56:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	char	**cmds;
	char	*input;
	char	*curdir;
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	int		quit;
	t_list	cmd;
}	t_minishell;

typedef struct s_argv
{
	char	**argv;
}	t_argv;

char	**cmd_split(char const *s);

#endif
