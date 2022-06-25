/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:11:30 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/25 17:18:03 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal
{
public:
	Cat(void);
	Cat(const Cat *tmp);
	Cat(const std::string name);
	~Cat(void);

	Cat &operator=(const Cat &tmp);

	std::string getType(void) const;

	void makeSound(void) const;
};

#endif