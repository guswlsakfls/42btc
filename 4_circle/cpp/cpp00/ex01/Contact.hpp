/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:53:49 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/17 17:59:44 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <iostream>
# include <string>

class Contact
{
private:
	int				index;
	std::string		firstName;
	std::string		lastName;
	std::string		nickName;
	std::string		phoneNumber;
	std::string		darkestSecret;
	static const std::string	fieldNames[5]; // 이거 왜함?

public:
	Contact(); // 생성자
	~Contact(); // 소멸자

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
