/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:21:04 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/25 14:29:58 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(void) : ClapTrap("DiamondT_clap_name"), ScavTrap(), FragTrap(), name("DiamondT") {
	this->hitPoint = FragTrap::hitPoint;
	this->attackDamage = FragTrap::attackDamage;
	this->energyPoints = ScavTrap::energyPoints;
	std::cout << "DiamondTrap default construct called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &tmp) : ClapTrap(tmp), ScavTrap(tmp), FragTrap(tmp), name(tmp.name) {
	this->hitPoint = FragTrap::hitPoint;
	this->attackDamage = FragTrap::attackDamage;
	this->energyPoints = ScavTrap::energyPoints;
	std::cout << "DiamondTrap copy construct called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string const name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), name(name) {
	this->hitPoint = FragTrap::hitPoint;
	this->attackDamage = FragTrap::attackDamage;
	this->energyPoints = ScavTrap::energyPoints;
	std::cout << "DiamondTrap name construct called" << std::endl;
}

DiamondTrap::~DiamondTrap(void) {
	std::cout << "DiamondTrap Destructor called" << std::endl;
}

void DiamondTrap::attack(std::string const &target) {
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void) {
	std::cout << "my name is " << this->name << ", ClapTrap name is " << ClapTrap::name << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &tmp) {
	ClapTrap::operator=(tmp);
	this->name = tmp.name;
	std::cout << "DiamondTrap Assignation operator called" << std::endl;
	return (*this)
}