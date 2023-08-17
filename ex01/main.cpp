/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:36:25 by corellan          #+#    #+#             */
/*   Updated: 2023/08/17 10:34:38 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av)
{
	RPN			calculations;
	std::string	temp;

	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	temp.clear();
	temp.append(av[1]);
	try
	{
		calculations.initialize(temp);
	}
	catch(const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}
