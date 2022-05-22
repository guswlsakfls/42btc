/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 17:57:25 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/22 18:22:44 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(const std::string type) : type_(type) {};

Weapon::~Weapon() {}

void Weapon::setType(std::string type) { type_ = type; }

const std::string &Weapon::getType() const { return (type_); }

