/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:09:09 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/23 22:31:18 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_from(char *nbr, char *b_from)
{
	int	i;

	i = 0;
	while (*nbr)
	{
		while (b_from[i])
		{
			if (b_from[i] == *nbr)
				return (i);
			i++;
		}
		nbr++;
	}
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_whitespace(char c)
{
	if (c == '\f' || c == '\n' || c == '\r')
		return (1);
	if (c == '\t' || c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	ft_base_erorr(char *base, int b_len)
{
	int	i;
	int	j;

	if (b_len <= 1)
		return (1);
	i = 0;
	while (i < b_len)
	{
		if (ft_whitespace(base[i]))
				return (1);
		j = i + 1;
		while (j < b_len)
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		if (base[i] == '+' || base[i] == '-')
			return (1);
		i++;
	}
	return (0);
}
