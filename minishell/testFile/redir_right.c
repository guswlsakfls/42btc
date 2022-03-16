#include "minishell.h"

void	ft_child(t_list *token_lst, char **envp, t_minishell *minishell)
{
	int		fd;
	char	*input;

	fd = open(".tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		exit(1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(1);
		if (ft_strncmp(input, "end", ft_strlen("end")) != 0)
		{
			ft_putstr_fd(input, fd);
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
	printf("\n\ntestshell\n\n");
	while (1)
	{
		minishell->input = readline("> ");
		open("temp.txt", O_WRONLY, O_CREAT, O_TRUNC, 0777);
		token_lst = analyze(minishell->input);
		ft_nanoshell(token_lst, envp, minishell);
		printf("token : %s\n", ((t_token *) token_lst->content)->str);
	}
	return (0);
}
