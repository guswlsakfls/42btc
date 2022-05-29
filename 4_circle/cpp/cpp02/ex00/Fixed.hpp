/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:31:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/27 15:50:24 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
private:
	int value_;
	static const int fracBits_ = 8;

public:
	Fixed();
	~Fixed();
	Fixed(const Fixed &src);

	int getRawBits() const;
	void setRawBits(const int raw);

	Fixed &operator=(const Fixed &src);
};

#endif
