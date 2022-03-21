/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/21 16:43:49 by hyunjinjo        ###   ########.fr       */
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

# define ISPIPE 1

typedef struct s_env
{
	char *key;
	char *value;
}	t_env;

	typedef struct s_cursor
{
	t_list *start;
	t_list *pre_pipe;
} t_cursor;

typedef struct s_pline
{
	t_list *ifile;
	t_list *ofile;
	char **cmds;
	int cnt;
	int pipe_fd[2];
	int file_fd[2];
	int heredoc_fd[2];
	int is_pipe;
	int	pid;
} t_pline;

typedef struct s_token
{
	int type;
	char *str;
} t_token;

void ft_here_doc(t_list heredoc);
void ft_redir(t_list plines);

//dha

char	**cmd_split(char *s);

# define CMD 1
# define PIPE 2
# define IREDIR 4
# define OREDIR 8
# define APPEND 16
# define HEREDOC 32

// analyze
t_list *analyze(char *cmd);
void tokens_clear(t_list **tokens);
// tokenize
t_list *tokenize(char *cmd);
int is_symbol(char *cmd);
int token_type(char *cmd);
void token_clear(t_list **lst, void (*del)(void *));
// merge
t_list *merge_token(t_list *tokens);
int get_type(t_list *token);
int parse_cmd(t_pline *pline, t_list **token);
int close_front_pipe(t_list **plines, int flag, t_cursor *cur, t_list **token);
void ft_stradd(t_pline *pline, int *idx, char *new);
t_token *token_dup(t_token *token);

// dha

#endif
