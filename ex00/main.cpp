/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:42:02 by corellan          #+#    #+#             */
/*   Updated: 2023/08/13 11:19:33 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int ac, char **av)
{
	BitcoinExchange	*data;
	std::string		tmp;

	data = NULL;
	if (ac != 2)
	{
		if (ac == 1)
			std::cerr << "Error: could not open file." << std::endl;
		else
			std::cerr << "Error: too many arguments." << std::endl;
		return (1);
	}
	tmp = av[1];
	try
	{
		data = new BitcoinExchange(tmp);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	delete data;
	return (0);
}