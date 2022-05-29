/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:10:35 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/28 18:02:59 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : value_(0) {}

Fixed::Fixed(const int value) { value_ = value << bits_; }

Fixed::Fixed(const float value) { value_ = roundf(value * (1 << bits_)); }

Fixed::Fixed(const Fixed &src) { *this = src; }

Fixed::~Fixed() {}

int Fixed::getRawBits() const { return (value_); }

void Fixed::setRawBits(int const raw) { value_ = raw; }

int Fixed::toInt() const { return (value_ >> bits_); }

float Fixed::toFloat() const { return (float(value_) / (1 << bits_)); }

Fixed &Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed const &Fixed::min(Fixed const &f1, Fixed const &f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed &Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}

Fixed const &Fixed::max(Fixed const &f1, Fixed const &f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return (out);
}

Fixed &Fixed::operator=(Fixed const &src)
{
	value_ = src.value_;
	return (*this);
}

bool Fixed::operator>(Fixed const &src) const { return (value_ > src.value_); }

bool Fixed::operator<(Fixed const &src) const { return (value_ < src.value_); }

bool Fixed::operator>=(Fixed const &src) const { return (value_ >= src.value_); }

bool Fixed::operator<=(Fixed const &src) const { return (value_ <= src.value_); }

bool Fixed::operator==(Fixed const &src) const { return (value_ == src.value_); }

bool Fixed::operator!=(Fixed const &src) const { return (value_ != src.value_); }

Fixed Fixed::operator+(Fixed const &src) const { return (Fixed(toFloat() + src.toFloat())); }

Fixed Fixed::operator-(Fixed const &src) const { return (Fixed(toFloat() - src.toFloat())); }

Fixed Fixed::operator*(Fixed const &src) const { return (Fixed(toFloat() * src.toFloat())); }

Fixed Fixed::operator/(Fixed const &src) const { return (Fixed(toFloat() / src.toFloat())); }

Fixed &Fixed::operator++()
{
	value_++;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed f(*this);

	value_++;
	return (f);
}

Fixed &Fixed::operator--()
{
	value_--;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed f(*this);

	value_--;
	return (f);
}
