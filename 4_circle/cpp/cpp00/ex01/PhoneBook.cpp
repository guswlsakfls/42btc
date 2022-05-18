/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:27:56 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/18 17:32:03 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	m_contactNums = 0;
	m_cursor = 0;
}

PhoneBook::~PhoneBook()
{
}

void	PhoneBook::addContact(void)
{
	m_contacts[m_cursor].promptContact(m_cursor + 1);
	m_cursor = (m_cursor + 1) % 8;
	m_contactNums < 8 ? m_contactNums++ : NULL;
}

void	PhoneBook::displayContacts(void)
{
	const std::string	*headers = m_contacts[0].getFieldNames();
	std::string			*contents;

	std::cout << '\t' << "|" << std::setw(10) << "INDEX";
	for (int i = 0; i < 4; i++)
		std::cout << "|" << std::setw(10) << headers[i];
	std::cout << "|" << std::endl;

	for (int i = 0; i < m_contactNums; i++)
	{
		contents = m_contacts[i].getFieldContents();
		std::cout << '\t' << "|" << std::setw(10) << i + 1;
		for (int j = 0; j < 4; j++)
		{
			if (contents[j].length() > 10)
				std::cout << "|" << contents[j].substr(0, 9) << ".";
			else
				std::cout << "|" << std::setw(10) << contents[j];
		}
		delete[] contents;
		std::cout << "|" << std::endl;
	}
}

void	PhoneBook::searchContact(void)
{
	int	index;

	displayContacts();
	if (m_contactNums == 0)
		std::cout << "# CONTACTS EMPTY: Add some before searching" << std::endl;
	else
	{
		std::cout << "# Select contact by index, select 0 to go back: ";
		while (!(std::cin >> index) || index < 0 || index > m_contactNums)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			std::cout << "# NOT A VAILD INDEX... TRY AGAIN: ";
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (index > 0)
			selectContact(index - 1);
	}
}

void	PhoneBook::selectContact(int index)
{
	const std::string	*headers = m_contacts[0].getFieldNames();
	std::string			*contents;

	contents = m_contacts[index].getFieldContents();
	std::cout << "# CONTACT NUMBER " << index + 1 << std::endl;
	for (int i = 0; i < 5; i++)
		std::cout << '\t' << headers[i] << ": " << contents[i] << std::endl;
	delete[] contents;
}

void	PhoneBook::open(void)
{
	std::string	cmd;

	std::cout << "# HELLOW PHONEBOOK #" << std::endl;
	while (1)
	{
		std::cout << "# INPUT YOUR COMMAND [ADD or SEARCH or EXIT]: ";
		std::getline(std::cin, cmd);
		if (cmd == "ADD")
			this->addContact();
		else if (cmd == "SEARCH")
			this->searchContact();
		else if (cmd == "EXIT")
		{
			std::cout << "# CLOSING PHONEBOOK... THANK YOU #" << std::endl;
			break ;
		}
		else
			std::cout << "TRY AGAIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	}
}
