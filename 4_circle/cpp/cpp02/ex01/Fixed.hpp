/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:31:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/28 17:22:36 by hyujo            ###   ########.fr       */
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
	static const int fracBits_ = 8;

public:
	Fixed();
	Fixed(const int interger);
	Fixed(const float flt);
	Fixed(const Fixed &src);
	~Fixed();

	int getRawBits() const;
	void setRawBits(const int raw);
	int toInt() const;
	float toFloat() const;

	Fixed &operator=(const Fixed &src);
};

std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif
