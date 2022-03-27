/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/27 16:19:44 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>

typedef struct s_cmds
{
	char			**cmds;
	int				argc;
	bool			is_pipe;
	int				fd[2];
	struct s_cmds	*prev;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_minishell
{
	int		pipe_fd[2];
	char	*input;
	char	*curdir;
	int		argc;
	char	**argv;
	char	**envp;
	char	**path;
	int		quit;
}	t_minishell;

typedef struct s_pline
{
	t_list *ifile;
	t_list *ofile;
	char *cmd;
	int	cnt;
	int pipe_fd[2];
	int file_fd[2];
	int is_pipe;
} t_pline;

typedef struct s_token
{
	int type;
	char *str;
} t_token;

void	ft_execute(char *str, char **envp);
void	ft_free_two(char ***split);
char	*ft_get_envp(char	**envp, char *var);
char	*ft_get_path(char *cmd, char **envp);

//dha

char	**cmd_split(char *s);

# define CMD 1
# define PIPE 2
# define IREDIR 4
# define OREDIR 8
# define APPEND 16
# define HEREDOC 32

t_list	*analyze(char *cmd);
t_list	*tokenize(char *cmd);
int		is_symbol(char *cmd);
int		token_type(char *cmd);

// dha

#endif
