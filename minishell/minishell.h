/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/11 18:35:10 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	int		pipe_fd[2];
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

typedef struct s_cmds
{
	char	**cmds;
	// int		redirect_stream;
	// t_bool	is_redirect;
	// t_bool	is_heredoc;
	// t_bool	is_stream;
	// t_bool	was_pipe;
	// t_bool	is_pipe;
	// t_bool	is_and;
	// t_bool	is_or;
	// t_bool	is_wildcard;
	// t_bool	hav_cmd;
}	t_cmds;

//dha

char	**cmd_split(char *s);

# define STR 1
# define PIPE 2
# define REDIR 4
# define SQUOTE 8
# define DQUOTE 16

typedef struct s_token {
	int		type;
	char	*str;
}				t_token;

t_list	*analyze(char *cmd);
t_list	*tokenize(char *cmd);
int		is_symbol(char *cmd);
int		token_type(char *cmd);

#endif
