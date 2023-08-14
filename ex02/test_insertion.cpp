/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_insertion.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:03:05 by corellan          #+#    #+#             */
/*   Updated: 2023/08/14 18:26:56 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void	insertionSort(int *array, int const &ammount)
{
	int	i;
	int	j;
	int	current;

	i = 1;
	while (i < ammount)
	{
		current = array[i];
		j = (i - 1);
		while ((j >= 0) && (array[j] > current))
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = current;
		i++;
	}
}

int	main(void)
{
	int	i;
	int	array[7] = {2, 7, 10, 4, 0, 20, 3};
	int	ammount	= sizeof(array)/sizeof(array[0]);
	i = 0;
	insertionSort(array, ammount);
	while (i < ammount)
	{
		std::cout << array[i] << ",";
		i++;
	}
	std::cout << std::endl;
	return (0);
}