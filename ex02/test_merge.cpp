/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_merge.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:18:49 by corellan          #+#    #+#             */
/*   Updated: 2023/08/15 17:49:03 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque>
#include <iostream>

void	merge(std::deque<unsigned int> &arr, int left, int middle, int right)
{
	int	n1;
	int	n2;
	int	k;
	int	l;
	int	o;

	n1 = ((middle - left) + 1);
	n2 = (right - middle);
	k = 0;
	l = 0;
	o = left;
	std::cout << "left:" << left << ". middle:" << middle << ". right:" << right << std::endl;
	std::deque<unsigned int>	leftSublist(n1);
	std::deque<unsigned int>	rightSublist(n2);
	for (int i = 0; i < n1; i++)
		leftSublist[i] = arr[left + i];
	for (size_t j = 0; j < n2; j++)
		rightSublist[j] = arr[middle + j + 1];
	while ((k < n1) && (l < n2))
	{
		if (leftSublist[k] <= rightSublist[l])
		{
			arr[o] = leftSublist[k];
			k++;
		}
		else
		{
			arr[o] = rightSublist[l];
			l++;
		}
		o++;
	}
	while (k < n1)
	{
		arr[o] = leftSublist[k];
		k++;
		o++;
	}
	while (l < n2)
	{
		arr[o] = rightSublist[l];
		l++;
		o++;
	}
	return ;
}

void	mergeSort(std::deque<unsigned int> &arr, int left, int right)
{
	int	middle;

	middle = 0;
	if (left < right)
	{
		middle = ((left + ((right - left) / 2)));
		mergeSort(arr, left, middle);
		mergeSort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}

int	main(void)
{
	std::deque<unsigned int>			arr;
	std::deque<unsigned int>::iterator	it;	
	int									n;

	arr.push_back(8348);
	arr.push_back(33434);
	arr.push_back(5453435);
	arr.push_back(12);
	arr.push_back(934);
	arr.push_back(254);
	arr.push_back(7546);
	arr.push_back(665);
	arr.push_back(465);
	n = arr.size();
	it = arr.begin();
	mergeSort(arr, 0, (n - 1));
	while (it != arr.end())
	{
		std::cout << *it << ",";
		it++;
	}
	std::cout << std::endl;
	return (0);
}