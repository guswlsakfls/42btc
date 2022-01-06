/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:55:40 by hyujo             #+#    #+#             */
/*   Updated: 2022/01/06 15:11:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"

# define ERR -1

typedef struct s_flags
{
	int	minus;
	int	zero;
	int	width;
	int	prec;
	int	deci;
	int	hex;
	int	plus;
	int	space;
	int	hash;
}	t_flags;

int				ft_printf(const char *fmt, ...);
int				ft_print_space_or_zero(t_flags *flags);
int				ft_parsing(char **fmt, va_list *ap, t_flags *flags);
int				ft_print_space_or_zero(t_flags *flags);
int				ft_to_nbr(char **fmt);
void			ft_check_flags(t_flags *flags, char **fmt);
int				ft_print_xX(unsigned long nb, char *fmt);
int				ft_type_xX(unsigned long nb, t_flags *flags, char *fmt);
int				ft_print_p(unsigned long nb);
int				ft_type_p(unsigned long nb, t_flags *flags);
int				ft_print_di(long nb);
unsigned int	ft_print_u(unsigned int nb);
int				ft_len_base(long nb, int base);
int				ft_type_di(long nb, t_flags *flags);
unsigned int	ft_type_u(unsigned int nb, t_flags *flags);
int				ft_type_percent(t_flags *flags);
int				ft_type_char(char c, t_flags *flags);
int				ft_type_str(char *str, t_flags *flags);

#endif
