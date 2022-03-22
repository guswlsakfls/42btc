/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjinjo <hyunjinjo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/23 00:54:48 by hyunjinjo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_sig_handler(int signum)
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
	signal(SIGINT, ft_sig_handler); // CTRL + C
	signal(SIGQUIT, SIG_IGN);		// CTRL + /
}

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

char	*ft_get_envp(t_list	*env, char *key)
{
	t_list 	*list;

	list = env;
	while (list)
	{
		if (ft_strncmp(((t_env *)list->content)->key, key, ft_strlen(key)) == 0)
			return (((t_env *)list->content)->value);
		list = list->next;
	}
	return (NULL);
}

// char *ft_get_envp(char **envp, char *var)
// {
// 	int i;
// 	int len_var;

// 	i = 0;
// 	var = ft_strjoin(var, "=");
// 	len_var = ft_strlen(var);
// 	while (ft_strnstr(envp[i], var, len_var) == 0) // "=" 도 더함
// 	{
// 		if (envp[i] == NULL)
// 		{
// 			free(var);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	free(var);
// 	return (&(envp[i][len_var]));
// }

// char	*ft_get_path(char *cmd, t_list *env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path_list;
// 	char	*path;

// 	paths = ft_split(ft_get_envp(envp, "PATH"), ':');
// 	i = -1;
// 	while (paths[++i])
// 	{
// 		path_list = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(path_list, cmd);
// 		if (access(path, F_OK) == 0)
// 		{
// 			ft_free_two(&paths);
// 			free(path_list);
// 			return (path);
// 		}
// 		free(path);
// 		free(path_list);
// 	}
// 	ft_free_two(&paths);
// 	return (0);
// }

char *ft_get_path(char *cmd, t_list *env)
{
	int 	i;
	char 	**paths;
	char 	*path_list;
	char 	*path;

	paths = ft_split(ft_get_envp(env, "PATH"), ':');
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

void	ft_execute(char **cmds, t_list *env, char **envp)
{
	char	*path;

	path = (ft_get_path(cmds[0], env));
	if (execve(path, cmds, envp) < 0)
	{
		//error 처리 해주기
		exit(1);
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

int	ft_built_in(char *cmd)
{
	if ((ft_strncmp(cmd, "echo", 5)) == 0)
		// ft_echo();
		printf("echo\n");
	else if ((ft_strncmp(cmd, "cd", 3)) == 0)
		// ft_cd();
		printf("echo\n");
	else if ((ft_strncmp(cmd, "pwd", 4)) == 0)
		// ft_pwd();
		printf("echo\n");
	else if ((ft_strncmp(cmd, "env", 4)) == 0)
		// ft_env();
		printf("echo\n");
	else if ((ft_strncmp(cmd, "export", 7)) == 0)
		// ft_export();
		printf("echo\n");
	else if ((ft_strncmp(cmd, "unset", 6)) == 0)
		// ft_unset();
		printf("echo\n");
	else if ((ft_strncmp(cmd, "exit", 5)) == 0)
		// ft_exit();
		printf("echo\n");
	return (0);
}

void	ft_check_pipe(t_pline *pline)
{
	if (pline->is_pipe == ISPIPE)
		if (pipe(pline->pipe_fd) < 0)
			exit(0);
}

void	ft_fork(t_list *plines, t_pline *cur, t_list *env, char **envp)
{
	t_pline	*prev;

	if (plines->prev)
		prev = ((t_pline *)plines->prev->content);
	// 포크할 필요가 없으면 pid == 0 으로 들어가 처리 한다.
	cur->pid = 0;
	if (cur->is_pipe == ISPIPE || ft_built_in(cur->cmds[0]) == 0) //  !(is_built_in)  // fork 는 파이프가 있거나 execve 를 쓰거나 할 때 분기 한다.
		cur->pid = fork();
	if (cur->pid < 0)
		exit(0);
	ft_signal(); // 자식 프로세스에서 시그널 처리이다.
	if (cur->pid > 0)
	{
		waitpid(cur->pid, NULL, WUNTRACED); // WUNTRACED
		// close(pline->pipe_fd[1]); // 지금 pipe_fd[1] 무조건 닫지
		if (prev && prev->pipe_fd[0]) // 이전 파이프 남아 있으면 닫자
			close(prev->pipe_fd[0]);
		if (cur->is_pipe == ISPIPE) // 여기 무한 루프 생겼음, 파이프 닫을 필요 없는데 닫아서 생김 슈발
			close(cur->pipe_fd[1]);
		if (cur->is_pipe == ISPIPE && plines->next == NULL) // 이거는 지금 파이프 인데 다음 커맨드 없으면 인듯?
			close(cur->pipe_fd[0]);
	}
	// 자식에서 pline->pipe_fd[0] 은 있으면 사용하고 닫음만 잘하자. 인에서 어차피 닫는다.
	if (cur->pid == 0)
	{
		// 자식에서 안쓰는 파이프 닫음
		if (cur->is_pipe == ISPIPE)
			close(cur->pipe_fd[0]);
		// 현재 인파일이 있으면 사용
		if (cur->file_fd[0] != 0)
		{
			dup2(cur->file_fd[0], STDIN_FILENO);
			close(cur->file_fd[0]);
		}
		// 이전에 파이프이고 아웃파일 없으면 넘어온거 사용
		else if (prev && prev->is_pipe == ISPIPE && prev->file_fd[1] == 0)
		{
			dup2(prev->pipe_fd[0], STDIN_FILENO);
			close(prev->pipe_fd[0]);
		}
		// close(pline->pipe_fd[0]); // 인파이프 중복 나중에 최적화 하자! // 그냥 입력 필요 없
		// 아웃파일 있으면
		if (cur->file_fd[1] != 0)
		{
			dup2(cur->file_fd[1], STDOUT_FILENO);
			close(cur->file_fd[1]);
			// if (cur->is_pipe == ISPIPE)
			close(cur->pipe_fd[1]); // 아웃파일이 있으니 아웃파이프 꼭 다 닫기
		}
		// 아웃파일 없고 파이프면
		else if (cur->is_pipe == ISPIPE && cur->file_fd[1] == 0)
		{
			dup2(cur->pipe_fd[1], STDOUT_FILENO);
			close(cur->pipe_fd[1]); // 이거 추가함
		}
		// if (ft_bulit_in(str, envp) == true)
		// 	exit(0);
		ft_execute(cur->cmds, env, envp);
	}
}

void	ft_nanoshell(t_list *plines, t_list *env, char **envp)
{
	t_list	*cur_plines;
	t_pline	*pline;

	cur_plines = plines;
	ft_redirection(cur_plines); // 리스트를 순회하며 infile 과 outfile 나온 fd 를 plines 에 file_fd[2] 로 넣어 두고 사용.
	while (cur_plines)
	{
		pline = (t_pline *)cur_plines->content;
		ft_check_pipe(pline); // 파이프인지 체크, fork를 할지 말지 체크해야함. // ft_open_pipe() 는 여기에 들어가면 될 것 같음
		ft_fork(cur_plines, pline, env, envp); // if (is_pipe || is_not_built_in)
		// ft_close_pipe(); 현재 열린 파이프와 이전에 사용된 파이프를 close 해준다.
		// 자식 프로세스를 다 돌고 나올때 까지 부모는 기다려 준다.
		// if (pline->heredoc_fd[0] == pline->file_fd[0])
		// {
		// 	close(pline->heredoc_fd[0]);
		// 	close(pline->file_fd[0]);
		// }
		// if (pline->file_fd[0])
		// 	close(pline->file_fd[0]);
		cur_plines = cur_plines->next;
	}
		// close(pline->pipe_fd[0]);
		// close(pline->pipe_fd[1]);
		// ft_close_pipe() // 명령이 끝났으므로 열린 fd는 모두 close 해야 무한루프에 빠지지 않는다.
}

t_list *ft_init_env(char **envp)
{
	t_list *lst;
	t_env *env;
	char *tmp;
	int idx[2];

	idx[0] = 0;
	lst = NULL;
	while (envp[idx[0]])
	{
		idx[1] = 0;
		env = (t_env *)ft_malloc(sizeof(t_env), 1);
		tmp = ft_strdup(envp[idx[0]]);
		while (tmp[idx[1]] != '=')
			idx[1]++;
		tmp[idx[1]] = '\0';
		env->key = ft_strdup(tmp);
		env->value = ft_strdup(tmp + idx[1] + 1);
		ft_lstadd_back(&lst, ft_lstnew(env));
		free(tmp);
		idx[0]++;
	}
	return (lst);
}

int main(int argc, char ** argv, char** envp) //  int argc, char **argv, char **envp
{
	t_list 	*plines;
	t_list	*env;

	if (argc > 2)
		exit(1);
	if (argv[0] == NULL)
		exit(1);
	// 처음에 envp 초기화 해서 가지고 다녀야 한다.
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	env = ft_init_env(envp);
	ft_signal();	
	while (1)
	{
		plines = analyze(readline("\033[0;91m\033[1mdha's Prompt$ \033[0m"));
		ft_nanoshell(plines, env, envp);
		free(plines);
	}
	return (0);
}