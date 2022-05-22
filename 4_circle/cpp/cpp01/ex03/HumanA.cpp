/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:04:30 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 18:25:29 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(const std::string name, Weapon &weapon) :
			name_(name), weapon_(weapon) {};

HumanA::~HumanA() {};

void HumanA::attack() { std::cout << name_ << " attacks with their " << weapon_.getType() << std::endl;}
