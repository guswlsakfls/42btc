/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:27:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/24 09:46:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : name("default"), hitPoint(10), energyPoints(10), attackDamage(0) {
	std::cout << "default constructor called" << std::endl;
}

ClapTrap::~ClapTrap(void) {
	std::cout << "destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name_) : name(name_), hitPoint(10), energyPoints(10), attackDamage(0) {
	std::cout << "constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &tmp) : name(tmp.name), hitPoint(tmp.hitPoint), energyPoints(tmp.energyPoints), attackDamage(tmp.attackDamage) {
	std::cout << "copy constructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src) {
	name = src.name;
	hitPoint = src.hitPoint;
	energyPoints = src.energyPoints;
	attackDamage = src.attackDamage;
	std::cout << "Assignation operator called" >> std::endl;
	return (*this);
}

void ClapTrap::attack(std::string const &target) {
	std::cout << "ClapTrap " << name << " attacks " << target << \
		", causing " << attackDamage << " points of damage! " << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	std::cout << "ClapTrap " << name << " has taken " << amount << " points of damage " << std::endl;
	if ((energyPoints - amount) <= 0)
	{
		energyPoints = 0;
		std::cout << "energyPoints is 0, ClapTrap " << name << " is died" << std::endl;
	}
	else
	{
		energyPoints -= amount;
		std::cout << "ClapTrap" << name << " energyPoints" << " : " << energyPoints << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (energyPoints == 0)
	{
		std::cout << "ClapTrap " << name << " is died, can't repair" << std::endl;
	}
	else
	{
		std::cout << "ClapTrap " << name << " is reapaired " << "+" << amount << std::endl;
		energyPoints += amount;
	}
}

int ClapTrap::getAd(void) {
	return (attackDamage);
}

void ClapTrap::setAd(unsigned int amount) {
	attackDamage = amount;
}