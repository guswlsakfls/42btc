/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:53:49 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/18 15:38:35 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

class Contact
{
private:
	int							m_index;
	std::string					m_firstName;
	std::string					m_lastName;
	std::string					m_nickName;
	std::string					m_phoneNumber;
	std::string					m_darkestSecret;
	static const std::string	m_fieldNames[5];

public:
	Contact();
	~Contact();

	void				setFirstName(std::string firstName);
	std::string			getFirstName(void);

	void				setLastName(std::string lastName);
	std::string			getLastName(void);

	void				setNickName(std::string nickname);
	std::string			getNickName(void);

	void				setPhoneNumber(std::string phoneNumber);
	std::string			getPhoneNumber(void);

	void				setDarkestSecret(std::string darkestSecret);
	std::string			getDarkestSecret(void);

	const std::string	*getFieldNames(void);
	std::string			*getFieldContents(void);

	void				promptContact(int index);
};

#endif
