/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/27 17:46:43 by hyujo            ###   ########.fr       */
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
	t_list			*ifile;
	t_list			*ofile;
	struct termios	org_term;
	struct termios	new_term;
	char			**cmds;
	int				cnt;
	int				pipe_fd[2];
	int				file_fd[2];
	int				heredoc_fd[2];
	int				is_pipe;
	int				pid;
}	t_pline;

typedef struct s_token
{
	int type;
	char *str;
} t_token;

// signal
void	ft_sig_heredoc(int signum);
void	ft_sig_cat(int signum);
void	ft_signal_ign();
void	ft_sig_quit(int signum);
void	ft_sig_int(int signum);
char	*ft_readline(char *status);
void	ft_signal_normal();
void	ft_signal_heredoc();
void	ft_reset_signal();

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

# define ERR_PRPT "nano: "
# define ERR_SYX "syntax error near unexpected token "
# define ERR_NVI "\': not a valid identifier"

# define ERROR -1

// analyze
t_list	*analyze(char *cmd, t_list *envs);
void    clear_tokens(t_list **tokens);
void	syntax_err_msg(int type);

// tokenize
t_list	*tokenize(char *cmd);
int		is_symbol(char *cmd);
int		token_type(char *cmd);

// merge
t_list	*merge_token(t_list *tokens);
int		get_type(t_list *token);
int		parse_cmd(t_pline *pline, t_list **token);
int		close_front_pipe(t_list **plines, int flag, t_cursor *cur, t_list **token);
void	ft_stradd(t_pline *pline, int *idx, char *new);
t_token	*token_dup(t_token *token);
t_list	*merge_err(t_list **plines, t_cursor *cur);

// optimize
void	optimize(t_list *plines, t_list *envs);
int		ft_envcnt(char *str);
char	*env_value(char *key, t_list *envs);
void	get_env_values(char **values, char **cmd, t_list *envs);
void	append_env_values(char **values, char **cmd);

//utils
int 	error_invalid_identifier(char *func, char *arg);
int		is_exist_key(char *key, t_list **envs);

// builtin
// echo
int	builtin_echo(char **argv, t_list **envs);
// cd
int	builtin_cd(char **argv, t_list **envs);
// pwd
int	builtin_pwd(char **argv, t_list **envs);
// env
int		builtin_env(char **argv, t_list **envs);

t_list	*ft_init_envs(char **envp);
// export
int 	builtin_export(char **argv, t_list **envs);
int		export_no_arg(t_list *envs);
int		export_arg(char *arg, t_list **envs);
// unset
int		builtin_unset(char **argv, t_list **envs);
// exit
int	builtin_exit(char **argv, t_list **envs);
// dha

#endif
