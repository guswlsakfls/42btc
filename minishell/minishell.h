/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/25 21:14:13 by hyunjinjo        ###   ########.fr       */
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

// signal
void ft_sig_cat(int signum);
void ft_signal_ign();
void ft_sig_quit(int signum);
void ft_sig_int(int signum);
char *ft_readline(char *status);
void ft_signal_normal();
void ft_signal_heredoc();
void ft_reset_signal();

// 다른거
void ft_redirection(t_list *plines);
void ft_input_heredoc(t_list *ifile, t_pline *pline);
int ft_built_in(char **cmds, t_list *env);
int ft_check_built_in(char *cmd);
void ft_echo(char **cmds);
bool ft_check_pwd(char *pwd);
void ft_cd(char **cmds, t_list *env);
char *ft_get_value(t_list *env, char *key);
char **ft_join_env(t_list *env);
char *ft_get_envp(char *cmd, t_list *env, char *key);
t_list *ft_init_env(char **envp);
void ft_execute(char **cmds, t_list *env, char **envp);
void ft_check_pipe(t_pline *pline);
void ft_fork(t_list *plines, t_pline *cur, t_list *env, char **envp);
void ft_nanoshell(t_list *plines, t_list *env, char **envp);
void ft_check_stdin(t_pline *cur, t_pline *prev);
void ft_check_stdout(t_pline *cur);
void ft_child(t_pline *cur, t_pline *prev, t_list *env, char **envp);
void ft_parent_close(t_list *plines, t_pline *cur, t_pline *prev);
void ft_parent(t_list *plines, t_pline *cur, t_pline *prev);
void ft_free_two(char ***split);

//dha

char **cmd_split(char *s);

# define CMD 1
# define PIPE 2
# define IREDIR 4
# define OREDIR 8
# define APPEND 16
# define HEREDOC 32

# define ERROR -1

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
