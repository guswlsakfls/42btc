/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:18:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/18 16:39:07 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iomanip>
# include <limits>
# include "Contact.hpp"

class PhoneBook
{
private:
	Contact	m_contacts[8];
	int		m_contactNums;
	int		m_cursor;

public:
	PhoneBook();
	~PhoneBook();

	void	addContact(void);
	void	displayContacts(void);
	void	searchContact(void);
	void	selectContact(int index);
	void	open(void);
};

#endif
