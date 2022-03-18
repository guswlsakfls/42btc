/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/18 18:31:05 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_two(char ***split)
{
	int	i;

	i = 0;
	if (*split == NULL)
		return ;
	while ((*split)[i] != NULL)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

char	*ft_get_envp(char	**envp, char *var)
{
	int		i;
	int		len_var;

	i = 0;
	var = ft_strjoin(var, "=");
	len_var = ft_strlen(var);
	while (ft_strnstr(envp[i], var, len_var) == 0) // "=" 도 더함
	{
		if (envp[i] == NULL)
		{
			free(var);
			return (NULL);
		}
		i++;
	}
	free(var);
	return (&(envp[i][len_var]));
}

char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path_list;
	char	*path;

	paths = ft_split(ft_get_envp(envp, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		path_list = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_list, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_two(&paths);
			free(path_list);
			return (path);
		}
		free(path);
		free(path_list);
	}
	ft_free_two(&paths);
	return (0);
}

int	ft_get_wd_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}

char	*ft_get_wd()
{
	char	*wd;
	char	**split_wd;
	int		size_split_wd;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (NULL);
	split_wd = ft_split(wd, '/');
	free(wd);
	size_split_wd = ft_get_wd_size(split_wd);
	if (size_split_wd == 1)
		wd = split_wd[0];
	else if (size_split_wd == 2)
		wd = ft_strdup("~");
	else
		wd = ft_strdup(split_wd[size_split_wd - 1]);
	ft_free_two(&split_wd);
	return (wd);
}

char	*ft_creat_prompt(char **envp)
{
	char	*wd;
	char	*env;
	char	*prompt;

	wd = ft_get_wd();
	wd = ft_strjoin(wd, " "); // ft_strjoin 안에서 free 시켜주는 거로
	env = ft_get_envp(envp, "USER");
	env = ft_strjoin(env, " ");
	prompt = ft_strjoin(env, wd);
	free(wd);
	return (ft_strjoin(prompt, "$ "));
}

void	ft_prompt(t_minishell *minishell
{
	char	*prompt;

	prompt = ft_creat_prompt(minishell->envp);
	// 명령 프롬프트 띄어서 사용자 입력 받음
	minishell->input = readline(prompt);
	add_history(minishell->input);
	if (minishell->input == NULL)
		exit(0);
}

void	ft_execute(char *cmd, char **envp)
{
	char	*path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	path = (ft_get_path(cmds[0], envp));
	if (execve(path, cmds, envp) < 0)
	{
		//error 처리 해주기.
	}
}

// void	ft_open_pipe(int pipe)
// {
// 	if (부모면)
// 		// close(minishell->pipe_fd[1]);
// 		// dup2(minishell->pipe_fd[0], STDIN_FILENO);
// 	else (자식이면)
// 		// close(minishell->pipe_fd[0]);
// 		// dup2(minishell->pipe_fd[1], STDOUT_FILENO);
// }

// void	ft_built_in(char *cmd)
// {
// 	if ((ft_strncmp(cmd, "echo", 5)) == 0)
// 		ft_echo();
// 	else if ((ft_strncmp(cmd, "cd", 3)) == 0)
// 		ft_cd();
// 	else if ((ft_strncmp(cmd, "pwd", 4)) == 0)
// 		ft_pwd();
// 	else if ((ft_strncmp(cmd, "env", 4)) == 0)
// 		ft_env();
// 	else if ((ft_strncmp(cmd, "export", 7)) == 0)
// 		ft_export();
// 	else if ((ft_strncmp(cmd, "unset", 6)) == 0)
// 		ft_unset();
// 	else if ((ft_strncmp(cmd, "exit", 5)) == 0)
// 		ft_exit();
// }

void	ft_check_pipe(t_cmds *cmd)
{
	// if (ft_pipe_check() == true)
	if (pipe(cmd->pipe_fd) < 0)
		exit(0);
}

void	ft_fork(t_cmds *cur_cmd, t_minishell *minishell)
{
	// 포크할 필요가 없으면 pid == 0 으로 들어가 처리 한다.
	cur_cmd->pid = 0;
	// if (is_pipe == true) || !(is_built_in)) // fork 는 파이프가 있거나 execve 를 쓰거나 할 때 분기 한다.
	cur_cmd->pid = fork();
	ft_signal(); // 자식 프로세스에서 시그널 처리이다.
	if (cur_cmd->pid < 0)
		exit(0);
	if (cur_cmd->pid == 0)
	{
		// 이전에 파이프였다면 이전 STDIN 값을 파이프로 가져온다.
		if (cur_cmd->previous && cur_cmd->previous->is_pipe)
		{
			dup2(cur_cmd->pipe_fd[0], STDIN_FILENO);
			close(cur_cmd->pipe_fd[1]);
		}
		// 다음 파이프가 있고, 아웃파일이 없다면. (만약 아웃파일이 있으면 아웃 파일로 STDOUT 해야 하기 때문)
		if (cur_cmd->is_pipe && !(cur_cmd->file_fd[1]))
		{
			close(cur_cmd->pipe_fd[0]);
			dup2(cur_cmd->pipe_fd[1], STDOUT_FILENO);
		}
		// if (ft_bulit_in(str, envp) == true)
		// 	exit(0);
		ft_execute(cur_cmd, minishell->envp);
	}
}

void	ft_nanoshell(t_cmds *cmds, t_minishell *minishell)
{
	t_cmds	*cur_cmd;

	cur_cmd = cmds;
	while (cur_cmd)
	{
		ft_redir(plines->pline, cur_cmd); // 리스트를 순회하며 infile 과 outfile 나온 fd 를 cur_cmd 에 file_fd[2] 로 넣어 두고 사용.
		// ft_check_pipe() // 파이프인지 체크, fork를 할지 말지 체크해야함. // ft_open_pipe() 는 여기에 들어가면 될 것 같음
		ft_fork(cur_cmd, minishell); // if (is_pipe || is_not_built_in)
		// ft_close_pipe(); 현재 열린 파이프와 이전에 사용된 파이프를 close 해준다.
		cur_cmd = cur_cmd->next;
	}
	// 자식 프로세스를 다 돌고 나올때 까지 부모는 기다려 준다.
	if (cur_cmd->pid > 0)
	{
	waitpid(cur_cmd->pid, NULL, 0);
	if (minishell->previous->pipe_fd[0])
		close(minishell->previous->pipe_fd[0]);
	close(minishell->pipe_fd[1]);
	}
	// ft_close_pipe() // 명령이 끝났으므로 열린 fd는 모두 close 해야 무한루프에 빠지지 않는다.
}

void	ft_sig_handler(int	signum)
{
	if (signum != SIGINT)
		return;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void ft_signal()
{
	signal(SIGINT, ft_sig_handler);  // CTRL + C
	signal(SIGQUIT, SIG_IGN); // CTRL + /
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;
	t_list		*plines;
	t_cmds		*cmd;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit(1);
	// 처음에 envp 초기화 해서 가지고 다녀야 한다.
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	ft_signal();
	while (1)
	{
		// 프롬프트 명령 띄울 때 현재 유저랑 디렉토리 나타내기
		ft_prompt(minishell);
		plines = analyze(minishell->input);
		// cmd = ft_create_cmds(plines) // 여기서 ft_redirection
		// 파싱한 cmds excute 할 것
		ft_nanoshell(cmd, minishell);
		// printf("token : %s\n", token_lst->content->str);
	}
	return (0);
}
