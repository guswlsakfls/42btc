/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:17:54 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/25 14:20:50 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamonTrap : public Scavtrap, public FragTrap
{
private:
	std::string name_;

public:
	DiamondTrap(void);
	DiamondTrap(const std::string name);
	DiamondTrap(const DiamondTrap &tmp);
	~DiamondTrap(void);

	DiamondTrap &operator=(const DiamondTrap &tmp);

	void attack(std::string const &target);
	void whoAmI(void);
}

#endif