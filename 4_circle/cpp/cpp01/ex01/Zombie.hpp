/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 11:04:32 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 16:57:03 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <cstdlib>

class	Zombie
{
private:
	std::string	m_name;
	int			m_num;

public:
	Zombie();
	~Zombie();

	void	announce(void);
	void	setName(int n, std::string name);

};

Zombie	*zombieHorde(int n, std::string name);

#endif
