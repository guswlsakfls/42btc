/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/31 20:11:53 by dha              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_mini
{
	struct termios	org_term;
	struct termios	new_term;
	int				statlog;
}	t_mini;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_cursor
{
	t_list	*start;
	t_list	*pre_pipe;
}	t_cursor;

typedef struct s_pline
{
	t_list	*ifile;
	t_list	*ofile;
	char	**cmds;
	int		cnt;
	int		pipe_fd[2];
	int		file_fd[2];
	int		heredoc_fd[2];
	int		is_pipe;
	int		pid;
}	t_pline;

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

// signal
void	ft_sig_heredoc(int signum);
void	ft_sig_int(int signum);
char	*ft_readline(char *status, t_list *env);

// termios
void	ft_termios_echoctl(t_mini *mini);
void	ft_termios_org(t_mini *mini);
void	ft_termios_new(t_mini *mini);

// redirection
int		ft_redirection(t_list *plines, t_mini *mini, t_list *env);
void	ft_get_heredoc(t_list *plines, t_mini *mini, t_list *env);
void	ft_close_file_fd(t_pline *pline);
int		ft_redir_ofile(t_pline *pline, t_list *ofile);

// utils2
void	ft_input_heredoc(t_list *ifile, t_pline *pline,
			t_mini *mini, t_list *env);
void	ft_child_heredoc(t_pline *pline, t_token *heredoc, t_list *env);
int		ft_redir_ifile(t_pline *pline, t_list *ifile);
void	ft_hredir(t_pline *pline);
int		ft_iredir(t_list *ifile, t_pline *pline);

// excute
void	ft_execute(char **cmds, t_list *env);
void	ft_check_pipe(t_pline *pline);
void	ft_check_stdin(t_pline *cur, t_pline *prev);
void	ft_check_stdout(t_pline *cur);
int		ft_child(t_pline *cur, t_pline *prev, t_list *env);
void	ft_parent_close(t_pline *cur, t_pline *prev);
void	ft_parent(t_pline *cur, t_pline *prev);
int		ft_check_statlog(t_mini *mini, t_list *cur_plines, t_list *env);

// nanoshell
void	ft_nanoshell(t_list *plines, t_list *env, t_mini *mini);
int		ft_check_stat_env(int statlog);
int		ft_fork(t_list *plines, t_pline *cur, t_list *env, t_mini *mini);
void	ft_check_cmds_null(t_pline *cur, t_list *plines);
void	ft_close_fd(t_list *plines);

// built_in
int		ft_built_in(char **cmds, t_list *env);
int		ft_check_built_in(char *cmd);
int		ft_check_file(t_pline *cur);

// envp
char	*ft_get_value(t_list *env, char *key);
char	**ft_join_env(t_list *env);
char	*ft_get_envp(char *cmd, t_list *env, char *key);
t_list	*ft_init_envs(char **envp);
char	*ft_value_list(char **values, char *cmd);

// main, error
void	ft_nanoshell(t_list *plines, t_list *env, t_mini *mini);
void	ft_free_two(char ***split);
int		ft_error_print(char *cmd, char *msg, int exitnum);
int		ft_error_execve(char **cmds);

// utils1
void	ft_check_pipe(t_pline *pline);
int		ft_check_file(t_pline *cur);
void	ft_backup_pid(int *backup_pid);
void	ft_waitpid(t_list *cur_plines, t_mini *mini, t_list *env, int status);

// utils2
void	ft_check_fork(t_pline *cur, t_pline *prev);
void	ft_init_exit_status(t_list	**envs);

//dha

char	**cmd_split(char *s, t_list *envs);

# define CMD 1
# define PIPE 2
# define IREDIR 4
# define OREDIR 8
# define HEREDOC 16
# define APPEND 32

# define ISPIPE 1

# define ERR_PRPT "nano: "
# define ERR_SYX "syntax error near unexpected token "
# define ERR_NVI "\': not a valid identifier"
# define ERR_ONS ": OLDPWD not set"
# define ERR_HNS ": HOME not set"
# define ERR_NMA ": numeric argument required"

# define ERROR -1

// analyze
t_list	*analyze(char *cmd, t_list *envs, t_mini *mini);
void	clear_tokens(t_list **tokens);
void	syntax_err_msg(int type);
void	set_exit_status(int value, t_list *env);

// tokenize
t_list	*tokenize(char *cmd, t_list *envs);
int		is_symbol(char *cmd);
int		token_type(char *cmd);

// merge
t_list	*merge_token(t_list *tokens, t_list *envs);
int		get_type(t_list *token);
int		parse_cmd(t_pline *pline, t_list **token);
int		close_front_pipe(t_list **plines, int flag, \
	t_cursor *cur, t_list **token);
void	ft_stradd(t_pline *pline, int *idx, char *new);
t_token	*token_dup(t_token *token);
t_list	*merge_err(t_list **plines, t_cursor *cur, t_list *envs);
void	clear_pline(void *pline);

// optimize
void	optimize(t_list *plines, t_list *envs);
int		ft_envcnt(char *str);
char	*env_value(char *key, t_list *envs);
void	get_env_values(char **values, char **cmd, t_list *envs);
void	append_env_values_iter(char **values, char **cmd, \
	char *new_cmd, int *idx);

//utils
int		error_invalid_identifier(char *func, char *arg);
int		is_exist_key(char *key, t_list **envs);

// builtin
// echo
int		builtin_echo(char **argv, t_list **envs);
// cd
int		builtin_cd(char **argv, t_list **envs);
// pwd
int		builtin_pwd(char **argv, t_list **envs);
// env
int		builtin_env(char **argv, t_list **envs);
// export
int		builtin_export(char **argv, t_list **envs);
int		export_no_arg(t_list *envs);
int		export_arg(char *arg, t_list **envs);
int		swap_value(char *value, t_list *envs);
// unset
int		builtin_unset(char **argv, t_list **envs);
// exit
int		builtin_exit(char **argv, t_list **envs);
// utils
int		is_exist_key(char *key, t_list **envs);
// error
int		error_invalid_identifier(char *func, char *arg);
int		error_env_not_set(char *func, char *arg);
int		error_numeric_arg(char *func, char *arg);

// dha

#endif
