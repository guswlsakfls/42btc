/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:27:29 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/24 13:29:36 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
public:
	FragTrap(void);
	FragTrap(const std::string name);
	FragTrap(const FragTrap &tmp);
	~FragTrap(void);

	FragTrap &operator=(const FragTrap &tmp);
	
	void attack(std::string const &target);
	void highFivesGuys(void);
};

#endif