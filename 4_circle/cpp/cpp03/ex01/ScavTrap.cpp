/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:03:52 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/24 13:24:48 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap("default") {
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTRap::ScavTrap(const std::string name) : ClapTRap(name) {
	std::cout << "ScavTrap name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &tmp) : CalpTrap() {
	name = tmp.name;
	hitPoint = tmp.hitPoint;
	energyPoints = tmp.energyPoints;
	attackDamage = tmp.attackDamage;
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap::~ScavTrap(void) {
	std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(std::string const &target) {
	std::cout << "ScavTrap " << name << " attacks " << target << \
		", causing " << attackDamage << " points of damage! " << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &tmp) {
	this->name = tmp.name;
	this->hitPoint = tmp.hitPoint;
	this->energyPoints = tmp.energyPoints;
	this->attackDamage = tmp.attackDamage;
	std::cout << "ScavTrap Assignation operator called" << std::endl;
	return (*this);


void ScavTrap::guardGate(void) {
	std::cout << "ScavTrap have entered in Gate keeper mode." << std::endl;
}