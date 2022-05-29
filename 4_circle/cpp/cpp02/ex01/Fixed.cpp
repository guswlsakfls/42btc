/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:33:47 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/28 18:18:27 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : value_(0) { std::cout << "Default constructor called" << std::endl; }

Fixed::Fixed(const int integer)
{
	std::cout << "Int constructor called" << std::endl;
	value_ = integer << fracBits_;
}

Fixed::Fixed(const float flt)
{
	std::cout << "Float constructor called" << std::endl;
	value_ = roundf(flt * (1 << fracBits_));
}

Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed &Fixed::operator=(const Fixed &src)
{
	std::cout << "Copy assignement operator called" << std::endl;
	value_ = src.getRawBits();
	return *this;
}

int Fixed::getRawBits() const { return value_; }

void Fixed::setRawBits(const int raw) { value_ = raw; }

int Fixed::toInt() const { return (value_ >> fracBits_); }

float Fixed::toFloat() const { return (float(value_) / (1 << fracBits_)); }

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}
