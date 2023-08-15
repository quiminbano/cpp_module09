/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:18:30 by corellan          #+#    #+#             */
/*   Updated: 2023/08/15 18:24:42 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	PmergeMe	*merge;

	if (ac == 1)
	{
		std::cout << "Error\n" << std::endl;
	}
	try
	{
		merge = new PmergeMe(av);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	delete merge;
	return (0);
}
