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

void	ft_prompt(t_minishell *minishell)
{
	char	*prompt;

	prompt = ft_creat_prompt(minishell->envp);
	// 명령 프롬프트 띄어서 사용자 입력 받음
	minishell->input = readline(prompt);
	add_history(minishell->input);
	if (minishell->input == NULL)
		exit(0);
}

char *ft_get_wd()
{
	char *wd;
	char **split_wd;
	int size_split_wd;

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

int ft_get_wd_size(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
		i++;
	return (i);
}