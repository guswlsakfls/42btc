/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:33:56 by hyujo             #+#    #+#             */
/*   Updated: 2021/12/19 10:53:45 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

void printf_digit(int args)
{
	va_list ap;

	va_start(ap, args);

	for (int i = 0; i < args; i++)
	{
		int num = va_args(ap, int);
		
		printf("%d\n", num);
	}
	va_end(ap);
}

int main()
{
	printf_digit(1, 10);
	printf_digit(2, 10, 20);
	printf_digit(3, 10, 20, 30);

	return (0);
}
