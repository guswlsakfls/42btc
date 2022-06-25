/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:04:54 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/25 17:11:12 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) : Animal("Dog") {
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog &tmp) : Animal(tmp.type) {
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog::Dog(const std::string name) : Animal(name) {
	std::cout << "Dog name constructor called" << std::endl;
}

Dog::~Dog(void) {
	std::cout << "Dog destructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &tmp) {
	Animal::operator=(tmp);
	std::cout << "Dog Assignation operator called" << std::endl;
	return (*this);
}

std::string Dog::getType(void) const {
	return (type);
}

void Dog::makeSound(void) const {
	std::cout << type << " : bawbaw" << std::endl;
}