/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:04:07 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 10:38:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
	Zombie *zombie1;

	zombie1 = new Zombie("Foo");
	zombie1->announce();
	randomChump("Joe");
	delete zombie1;
	return 0;
}
