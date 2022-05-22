/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:50:04 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 16:57:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	int n = 4;

	Zombie *zombies = zombieHorde(n, "Zombie");
	for (int i = 0; i < n; i++)
	{
		zombies[i].announce();
	}
	delete[] zombies;
	return (0);
}
