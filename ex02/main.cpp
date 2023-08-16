/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:18:30 by corellan          #+#    #+#             */
/*   Updated: 2023/08/16 08:47:55 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	PmergeMe	*merge;

	merge = NULL;
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
		return (1);
	}
	delete merge;
	return (0);
}
