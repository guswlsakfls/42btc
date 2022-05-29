/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujo <hyujo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:46:37 by hyujo             #+#    #+#             */
/*   Updated: 2022/05/23 14:47:27 by hyujo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char **argv)
{
	std::ifstream	fileIn;
	std::ofstream	fileOut;
	std::string		file;
	std::string		buf;
	size_t			i;

	if (argc != 4 || std::strlen(argv[2]) == 0)
	{
		std::cout << "Error: Not valid arguments" << std::endl;
		return (1);
	}

	file = argv[1];
	fileIn.open(file);
	if (fileIn.fail())
	{
		std::cout << "Error: Can't open '" << file << "'" << std::endl;
		return (1);
	}
	file.append(".replace");
	fileOut.open(file);
	if (fileOut.fail())
	{
		std::cout << "Error: Can't create '" << file << "'" << std::endl;
		return (1);
	}

	while (true)
	{
		std::getline(fileIn, buf);
		while (true)
		{
			i = buf.find(argv[2]);
			if (i == std::string::npos)
			{
				fileOut << buf;
				break ;
			}
			fileOut << buf.substr(0, i) << argv[3];
			buf = buf.substr(i + std::strlen(argv[2]));
		}
		if (fileIn.eof())
		{
			break ;
		}
		fileOut << std::endl;
	}
	
	fileIn.close();
	fileOut.close();
	return (0);
}
