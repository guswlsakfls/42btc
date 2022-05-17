/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:11:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/17 18:01:15 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

const std::string	Contact::fieldNames[5] =
{
	"FIRST NAME",
	"LAST NAME",
	"NICKNAME",
	"PHONE NBR",
	"DARKEST SECRET"
};

Contact::Contact()
{
}

Contact::~Contact()
{
}

void				Contact::setFirstName(std::string firstName) {this->firstName = firstName;}
std::string			Contact::getFirstName(void) {return (this->firstName);}

void				Contact::setLastName(std::string lastName) {this->lastName = lastName;}
std::string			Contact::getLastName(void) {return (this->lastName);}

void				Contact::setNickName(std::string nickName) {this->nickName = nickName;}
std::string			Contact::getNickName(void) {return (this->nickName);}

void				Contact::setPhoneNumber(std::string phoneNumber) {this->phoneNumber = phoneNumber;}
std::string			Contact::getPhoneNumber(void) {return (this->phoneNumber);}

void				Contact::setDarkestSecret(std::string darkestSecret) {this->darkestSecret = darkestSecret;}
std::string			Contact::getDarkestSecret(void) { return (this->darkestSecret);}

const std::string	*Contact::getFieldNames(void) {return (this->fieldNames);}

std::string			*Contact::getFieldContents(void)
{
	std::string		*contens = new std::string[5];
	contens[0] = this->firstName;
	contens[1] = this->lastName;
	contens[2] = this->nickName;
	contens[3] = this->phoneNumber;
	contens[4] = this->darkestSecret;
	return (contens);
}

void	Contact::promptContact(int index)
{
	this->index = index;
	std::cout << "# Input this fileds #" << std::endl;
	std::cout << "FIRST NAME : ";
	std::getline(std::cin, this->firstName);
	std::cout << "LAST NAME : ";
	std::getline(std::cin, this->lastName);
	std::cout << "NICK NAME : ";
	std::getline(std::cin, this->nickName);
	std::cout << "PHONE NUMBER : ";
	std::getline(std::cin, this->phoneNumber);
	std::cout << "DARKEST SECRET : ";
	std::getline(std::cin, this->darkestSecret);
}
