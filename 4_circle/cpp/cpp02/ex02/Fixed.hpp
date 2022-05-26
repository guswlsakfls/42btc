/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 19:03:48 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/26 20:52:31 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

class Fixed
{
private:
	int value_;
	const static int bits_ = 8;

public:
	Fixed();
	Fixed(const int fixed);
	Fixed(const float fixed);
	Fixed(const Fixed &src);
	~Fixed();

	Fixed &operator=(const Fixed &src);
	bool operator>(Fixed const &src) const;
	bool operator<(Fixed const &src) const;
	bool operator>=(Fixed const &src) const;
	bool operator<=(Fixed const &src) const;
	bool operator==(Fixed const &src) const;
	bool operator!=(Fixed const &src) const;
	Fixed operator+(fixed const &src) const;
	Fixed operator-(fixed const &src) const;
	Fixed operator*(fixed const &src) const;
	Fixed operator/(fixed const &src) const;
	Fixed &operator++();
	Fixed operator++(int);
	Fixed &operator--();
	Fixed operator--(int);

	int getRawBits() const;
	void setRawBits(int const raw);

	int toInt() const;
	float toFloat() const;

	static Fixed &min(Fixed &f1, Fixed &f2);
	static Fixed const &min(Fixed const &f1, Fixed const &f2);
	static Fixed &max(Fixed &f1, Fixed &f2);
	static Fixed const &max(Fixed const &f1, Fixed const &f2);
}

std::ostream &operator<<(std::ostream &s, const Fixed &fixed);

#endif
