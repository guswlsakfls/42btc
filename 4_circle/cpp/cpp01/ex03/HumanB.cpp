/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:11:09 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 18:25:09 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(const std::string name) : name_(name) { weapon_ = NULL;}
HumanB::~HumanB() {}

void HumanB::attack()
{
	if (!weapon_)
	{
		std::cout << name_ << " disarmed" << std::endl;
		return ;
	}
	std::cout << name_ << " attacks with their " << weapon_->getType();
	std::cout << std::endl;
}

void HumanB::setWeapon(Weapon &weapon) { weapon_ = &weapon; }
