/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:01:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/21 15:10:19 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_BONUS_H
# define FT_PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>

# define WRITE 0
# define READ 1

void	ft_execute(char *av, char **envp);
void	ft_child_process(char	*av, char **envp);
void	ft_here_doc(char **av);
int		ft_get_next_line(char **line);
void	ft_print_error(int num);
int		ft_check_slash(char *cmds);
void	ft_free(char **cmds);
char	*ft_get_path(char *cmd, char **envp);

#endif
