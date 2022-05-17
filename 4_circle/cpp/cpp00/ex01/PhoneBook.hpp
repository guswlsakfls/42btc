/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:18:51 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/16 16:22:19 by hyujo            ###   ########.fr       */
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
	Contact	contacts[8];
	int		n_contacts;
	int		cursor;

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
