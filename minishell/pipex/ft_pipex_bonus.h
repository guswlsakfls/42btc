/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:01:05 by hyujo             #+#    #+#             */
/*   Updated: 2022/02/22 12:06:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_BONUS_H
# define FT_PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

void	ft_execute(char *av, char **envp);
void	ft_child_process(char	*av, char **envp);
void	ft_here_doc(char **av);
int		ft_get_next_line(char **line);
void	ft_print_error(int num);
void	ft_free(char **cmds);
char	*ft_get_path(char *cmd, char **envp);

#endif
