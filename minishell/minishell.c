/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/16 18:57:55 by hyujo            ###   ########.fr       */
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

void	ft_prompt(t_minishell *minishell, char **envp)
{
	char	*prompt;

	prompt = ft_creat_prompt(envp);
	// 명령 프롬프트 띄어서 사용자 입력 받음
	minishell->input = readline(prompt);
	add_history(minishell->input);
	if (minishell->input == NULL)
		exit(0);
}

void	ft_execute(char *str, char **envp)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(str, ' ');
	path = (ft_get_path(str, envp));
	if (path)
		execve(path, cmds, envp);
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

void	ft_child(t_list *token_lst, char **envp, t_minishell *minishell)
{
	pid_t	pid;

	// if (pipe_check == true)
	if (pipe(minishell->pipe_fd) < 0)
		exit(0);
	pid = 0;
	// if (is_pipe || !built_in)
	pid = fork();
	ft_signal(); // 자식 프로세스에서 시그널 처리이다.
	if (pid < 0)
		exit(0);
	if (pid > 0)
	{
		// close(minishell->pipe_fd[1]);
		// dup2(minishell->pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	else
	{
		// close(minishell->pipe_fd[0]);
		// dup2(minishell->pipe_fd[1], STDOUT_FILENO);
		// ft_built_in(str, envp);
		ft_execute(((t_token *) token_lst->content)->str, envp);
	}
}

void	ft_here_doc(t_list infile, int fd)
{
	char	*input;

	fd = open(".tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit(1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(1);
		if (ft_strncmp(input, infile->name, ft_strlen(infile->name)) != 0)
		{
			ft_putstr_fd(input, fd); // 계속 데이터가 fd 파일에 쌓인다.
			ft_putstr_fd("\n", fd);
		}
		else
		{
			close(fd);
			free(input);
			break ;
		}
		free(input);
	}
	close(fd);
}

void	ft_redir(t_pline pline) // file open 이 에러가 나면 에러 메시지 띄우고 다음 파일 오픈으로 감
{
	t_list	infile;
	t_list	heredoc;
	t_list	outfile;
	int		fd;

	infile = pline->infile;
	outfile = pline->outfile;
	// heredoc 나오면 제일 먼저 임시파일 만들어 준다.
	heredoc = pline->infile;
	while (heredoc)
	{
		if (heredoc->type == HEREDOC)
			ft_here_doc(infile, fd);
		heredoc->next;
	}
	while (infile)
	{
		// < 일 때
		if (infile->type == IREDIR)
		{
			fd = open(infile->name, O_RDONLY, 0777);
			if (fd < 0)
				exit(1);
		}
		// << 일 때, here_doc 이다.
		else
		{
			fd = open(".tmp_heredoc", O_RDONLY, 0777);
			if (fd < 0)
				exit(1);
		}
		if (infile->type == IREDIR)
		{
			fd = open(infile->name, O_RDONLY, 0777);
			if (fd < 0)
				exit(1);
		}
		if (!(infile->next))
		{
			// dup2(fd, STDIN_FILENO); // 모든 입력이 fd 이다. // 자식에서 dup2 로 하면 될 듯?
			// if (dup < 0)
			// 	exit(1);
			// close(fd); // file 내용은 STDIN으로 복제 했으니까 닫아도 된다. // 닫으면 fd 파일은 계속 표준입출력에 복제 되나? => 지금까지 이해는 그렇다.
			// if (inifle->type == HEREDOC)
			// 	unlink(".tmp_heredoc");
			break ;
		}
		infile = infile->next;
	}
	while (outfile)
	{
		// > 일 때
		if (outfile->type == OREDIR)
		{
			fd = open(outfile->name, O_WRONLY, O_CREAT, O_TRUNC, 0777);
			if (fd < 0)
				exit(1);
		}
		else
		{
			fd = open(outfile->name, O_WRONLY, O_CREAT, O_APPEND, 0777);
			if (fd < 0)
				exit(1);
		}
		if (!(outfile->next))
		{
			// dup2(fd, STDOUT_FILENO);
			// if (dup < 0)
			// 	exit(1);
			// close(fd); // file 에 stdout cmd 명령에서 넣을껀데 닫아도 상관 없나?
			break ;
		}
		outfile = outfile->next;
	}
}

void	ft_nanoshell(t_list *token_lst, char **envp, t_minishell *minishell)
{
	t_list	*plines;

	plines = token_lst;
	while (plines)
	{
		// ft_create_cmds() // token 을 excute 하기위해 구조체를 다시 생성한다.
		// ft_check_pipe() // 파이프인지 체크, fork를 할지 말지 체크해야함.
		// ft_open_pipe()
		// ft_redir(plines->pline) // 리스트를 순회하며 infile 과 outfile 에 STDIN, STDOUT dup2 해줘야 함
		ft_child(plines, envp, minishell); // if (is_pipe || is_not_built_in)
		plines = plines->next;
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
	t_list		*token_lst;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit(1);
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->envp = envp;
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	ft_signal();
	while (1)
	{
		// 프롬프트 명령 띄울 때 현재 유저랑 디렉토리 나타내기
		ft_prompt(minishell, envp);
		token_lst = analyze(minishell->input);
		// 파싱한 cmds excute 할 것
		ft_nanoshell(token_lst, envp, minishell);
		// printf("token : %s\n", token_lst->content->str);
	}
	return (0);
}


if is_pipe 파이프 이면
	ft_pipe 
if 부모
	if is_pipe 
		dup2
	waitpid
