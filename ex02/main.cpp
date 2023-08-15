/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:18:30 by corellan          #+#    #+#             */
/*   Updated: 2023/08/15 22:26:19 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	PmergeMe	*merge;

	if (ac == 1)
	{
		std::cout << "Error" << std::endl;
		return (1);
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
