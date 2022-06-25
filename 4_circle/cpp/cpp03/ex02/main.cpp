/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:25:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/24 13:26:53 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FageTrap.hpp"

int main(void)
{
	FragTrap a;
	FragTrap b("smang");

	b.takeDamage(5);
	b.takeDamage(2);
	b.beRepaired(5);
	b.attack("ang");
	a = b;
	a.setAd(3);
	a.attack("ang");
	return (0);
}