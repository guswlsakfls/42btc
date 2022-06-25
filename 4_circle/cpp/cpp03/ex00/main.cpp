/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:47:04 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/24 09:48:24 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap a;
	ClapTrap b("sma");
	ClapTrap c(b);

	b.takeDamage(5);
	b.takeDamage(2);
	b.beRepaired(5);
	b.attack("ang");
	a = b;
	a.setAd(3);
	a.attack("ang");
	return (0);
}