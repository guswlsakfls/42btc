/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:27:56 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/17 19:20:47 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	this->n_contacts = 0;
	this->cursor = 0;
}

PhoneBook::~PhoneBook()
{
}

void	PhoneBook::addContact(void)
{
	this->contacts[this->cursor].promptContact(this->cursor + 1);
	this->cursor = (this->cursor + 1) % 8;
	this->n_contacts < 8 ? this->n_contacts++ : NULL;
}

void	PhoneBook::displayContacts(void)
{
	const std::string	*headers = this->contacts[0].getFieldNames();
	std::string			*contents;

	std::cout << "|" << std::setw(10) << "INDEX";
	for (int i = 0; i < 4; i++)
		std::cout << "|" << std::setw(10) << headers[i];
	std::cout << "|" << std::endl;

	for (int i = 0; i < this->n_contacts; i++)
	{
		contents = this->contacts[i].getFieldContents();
		std::cout << "|" << std::setw(10) << i + 1;
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

	this->displayContacts();
	if (this->n_contacts == 0)
		std::cout << "# CONTACTS EMPTY: Add some before searching" << std::endl;
	else
	{
		std::cout << "# Select contact by index, select 0 to go back:" << std::endl;
		while (!(std::cin >> index) || index < 0 || index > this->n_contacts)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			std::cout << "# Not a valid index. Try again:" << std::endl;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (index > 0)
			this->selectContact(index - 1);
	}
}

void	PhoneBook::selectContact(int index)
{
	const std::string	*headers = this->contacts[0].getFieldNames();
	std::string			*ccontents;

	ccontents = this->contacts[index].getFieldContents();
	std::cout << "# CONTACT NUMBER " << index + 1 << std::endl;
	for (int i = 0; i < 5; i++)
		std::cout << "\t" << headers[i] << ": " << ccontents[i] << std::endl;
	delete[] ccontents;
}

void	PhoneBook::open(void)
{
	std::string	cmd;

	std::cout << "# HELLOW PHONEBOOK #" << std::endl;
	std::cout << "# Input your command [ADD or SEARCH or EXIT]:" << std::endl;
	while (1)
	{
		std::cout << "COMMAND : ";
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
			std::cout << "Try again!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	}
}
