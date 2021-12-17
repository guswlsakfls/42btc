/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:47:27 by hyujo             #+#    #+#             */
/*   Updated: 2021/10/13 19:10:49 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	check_capitalize(char *now_str, int index);

char	*ft_strcapitalize(char *str)
{
	int index;

	index = 0;
	if ('a' <= str[0] && str[0] <= 'z')
	{
		str[0] -= 32;
	}
	index++;
	check_capitalize(str, index);
	return (str);
}

void	check_capitalize(char *now_str, int index)
{
	while (now_str[index] == '\0')
	{
		char ex_str;

		ex_str = now_str[index - 1];
		if (!(('a' <= ex_str && ex_str <= 'z') || ('A' <= ex_str && ex_str <= 'Z')))
		{
			if ((('a' <= now_str[index] && now_str[index] <= 'z')) && (!('0' <= ex_str && ex_str <= '9')))
			{
				now_str[index] -= 32;
			}
		}
		if ('A' <= now_str[index] && now_str[index] <= 'Z')
		{
			if ('0' <= ex_str && ex_str <= '0')
			{
				now_str[index] += 32;
			}
		}
		if (('A' <= ex_str && ex_str <= 'Z') && ('A' <= now_str[index] && now_str[index] <= 'Z'))
		{
			now_str[index] += 32;
		}
		if (('a' <= ex_str && ex_str <= 'z') && ('A' <= now_str[index] && now_str[index] <= 'Z'))
		{
			now_str[index] += 32;
		}
	}
}
