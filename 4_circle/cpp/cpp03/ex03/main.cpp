/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:30:22 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/25 14:31:51 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main(void)
{
	std::cout << "-----------------------------------------------------" << std::endl;

	DiamondTrap dia3;

	std::cout << "-----------------------------------------------------" << std::endl;

	DiamondTrap dia2("sma");

	std::cout << "-----------------------------------------------------" << std::endl;\

	dia3 = dia2;

	std::cout << "-----------------------------------------------------" << std::endl;

	dia2.whoAmI():
	dia3.whoAmI();

	std::cout << "-----------------------------------------------------" << std::endl;

	return (0);
	
}