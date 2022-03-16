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

void	ft_execute(char *str, char **envp)
{
	char	**cmds;
	char	*path;

	cmds = ft_split(str, ' ');
	path = (ft_get_path(str, envp));
	if (path)
		execve(path, cmds, envp);
}
