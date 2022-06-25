/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 16:53:03 by hyujo             #+#    #+#             */
/*   Updated: 2022/06/25 16:57:30 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
protected:
	std::string type_;

public:
	Animal(void);
	Animal(const Animal &tmp);
	Animal(const std::string name);
	virtual ~Animal(void); // 부모클래스 포인터에 자식클래스 객체를 대입해줄 때 소멸자를 가상함수로 선언해줘야 자식까지 소멸자가 호출 가능하다.

	Animal &operator=(const Animal &tmp);

	std::string getType(void) const;

	virtual void makeSound(void) const;
};

#endif