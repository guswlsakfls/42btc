/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:46:54 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 18:04:25 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include "Weapon.hpp"

class	HumanA
{
private:
	const std::string	name_;
	Weapon				&weapon_;

public:
	HumanA(const std::string name, Weapon &Weapon);
	~HumanA();
	void attack();
};

#endif
