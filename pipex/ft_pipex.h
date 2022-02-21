/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:22:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/21 15:42:27 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <fcntl.h>

void	ft_parent(char **av, char **envp);
void	ft_child(char **av, char **envp);
void	ft_parent_fd(int *pipe_fd, int *file_fd, char **av);
void	ft_child_fd(int *pipe_fd, int *file_fd, char **av);
void	ft_print_error(int num);
int		ft_check_slash(char *cmds);
void	ft_free(char **cmds);
char	*ft_get_path(char *cmd, char **envp);

#endif
