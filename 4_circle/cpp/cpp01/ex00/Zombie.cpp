/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 10:24:28 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 11:38:08 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : m_name(name)
{
	std::cout << "WaaaaaaaaakkkkkuuuuP..." << std::endl;
}

Zombie::~Zombie()
{
	std::cout << m_name << ": DiiiiiiiieeeeeddddD..." << std::endl;
}

void Zombie::announce()
{
	std::cout << Zombie::m_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
