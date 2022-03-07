/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:07:44 by hyujo             #+#    #+#             */
/*   Updated: 2022/03/07 18:26:11 by hyujo            ###   ########.fr       */
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
	for (int i = 0; split[i]; i++)
		printf("%s\n", split[i]);
	// system("leaks minishell");
	return (split);
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
	minishell->curdir = getcwd(NULL, 0);
	printf("\n\nNANOSHELL BY HYUJO & DHA\n\n");
	while (1)
	{
		minishell->input = readline("\033[0;91m\033[1mNano Prompt$ \033[0m");
		if (minishell->input == NULL)
			exit(0);
		minishell->cmds = parse(minishell->input);
		add_history(minishell->input);
	}
	return (0);
}
