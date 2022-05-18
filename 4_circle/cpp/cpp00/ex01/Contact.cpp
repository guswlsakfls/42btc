/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:11:21 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/18 17:25:02 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

const std::string	Contact::m_fieldNames[5] =
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

void				Contact::setFirstName(std::string firstName) {m_firstName = firstName;}
std::string			Contact::getFirstName(void) {return (m_firstName);}

void				Contact::setLastName(std::string lastName) {m_lastName = lastName;}
std::string			Contact::getLastName(void) {return (m_lastName);}

void				Contact::setNickName(std::string nickName) {m_nickName = nickName;}
std::string			Contact::getNickName(void) {return (m_nickName);}

void				Contact::setPhoneNumber(std::string phoneNumber) {m_phoneNumber = phoneNumber;}
std::string			Contact::getPhoneNumber(void) {return (m_phoneNumber);}

void				Contact::setDarkestSecret(std::string darkestSecret) {m_darkestSecret = darkestSecret;}
std::string			Contact::getDarkestSecret(void) { return (m_darkestSecret);}

const std::string	*Contact::getFieldNames(void) {return (m_fieldNames);}

std::string			*Contact::getFieldContents(void)
{
	std::string		*contens = new std::string[5];
	contens[0] = m_firstName;
	contens[1] = m_lastName;
	contens[2] = m_nickName;
	contens[3] = m_phoneNumber;
	contens[4] = m_darkestSecret;
	return (contens);
}

void	Contact::promptContact(int index)
{
	m_index = index;
	std::cout << "# INPUT THIS FIELDS #" << std::endl;
	std::cout << '\t' << "FIRST NAME : ";
	std::getline(std::cin, m_firstName);
	std::cout << '\t' << "LAST NAME : ";
	std::getline(std::cin, m_lastName);
	std::cout << '\t' << "NICK NAME : ";
	std::getline(std::cin, m_nickName);
	std::cout << '\t' << "PHONE NUMBER : ";
	std::getline(std::cin, m_phoneNumber);
	std::cout << '\t' << "DARKEST SECRET : ";
	std::getline(std::cin, m_darkestSecret);
}
