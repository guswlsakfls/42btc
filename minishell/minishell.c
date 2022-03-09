/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/09 14:56:05 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_get_path(char *cmd, char **envp)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path_list;
// 	char	*path;

// 	i = 0;
// 	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
// 		i++;
// 	paths = ft_split(envp[i] + 5, ':');
// 	i = -1;
// 	while (paths[++i])
// 	{
// 		path_list = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(path_list, cmd);
// 		if (access(path, F_OK) == 0)
// 		{
// 			ft_free(paths);
// 			free(path_list);
// 			return (path);
// 		}
// 		free(path);
// 		free(path_list);
// 	}
// 	ft_free(paths);
// 	return (0);
// }

// void	ft_get_cmd(t_minishell *minishell)
// {

// }

char	**parse(char *cmd)
{
	char	**split;

	if (!ft_strncmp("exit", cmd, 5))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	split = cmd_split(cmd);
	// system("leaks minishell");
	return (split);
}

int	ft_get_wd_size(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
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
	if (minishell->input == NULL)
		exit(0);
}

void	ft_excute(t_minishell *minishell)
{
	pid_t	pid;

	while ()
	{

	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		exit(1);
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->envp = envp;
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	while (1)
	{
		// 프롬프트 명령 띄울 때 현재 유저랑 디렉토리 나타내기
		ft_prompt(minishell, envp);
		minishell->cmds = parse(minishell->input);
		add_history(minishell->input);
		// 파싱한 cmds excute 할 것
		ft_execute(minishell);
	}
	return (0);
}
