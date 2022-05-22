/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:11:07 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 16:57:46 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{
	std::cout << "WaaaaaaaaakkkkkuuuuP..." << std::endl;
}

Zombie::~Zombie()
{
	std::cout << Zombie::m_num << "." << m_name << ": DiiiiiiiieeeeeddddD..." << std::endl;
}

void	Zombie::announce()
{
	std::cout << Zombie::m_num << "." << Zombie::m_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(int n, std::string name)
{
	m_name = name;
	m_num = n;
}
