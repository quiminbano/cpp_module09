/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:24:57 by corellan          #+#    #+#             */
/*   Updated: 2023/08/15 19:19:21 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
	if (_fillContainers(av) == -1)
		throw (Error());
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

int	PmergeMe::_fillContainers(char **av)
{
	str_vector	arrStr;

	arrStr = _countArgument(av);
}

str_vector	PmergeMe::_countArgument(char **av)
{
	size_t		i;
	str_vector	temp;

	i = 0;
	while (av[i])
	{
		temp.push_back(av[i]);
		i++;
	}
	return (temp);
}

size_t	PmergeMe::_countWords(std::string const &input)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] != ' ' ) && (input[i + 1] == ' ' || input[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

str_vector	PmergeMe::_splitcplusplus(std::string &input)
{
	str_vector	split;
	size_t		words;
	size_t		i;

	words = _countWords(input);
	i = 0;
	while (i < words)
	{
		input = input.substr(_countSpace(input));
		split[i] = input.substr(0, _findSpace(input));
		if ((i + 1) < words)
			input = input.substr(_findSpace(input) + _countSpace(input.substr(_findSpace(input))));
		i++;
	}
	return (split);
}

size_t	PmergeMe::_countSpace(std::string const &input)
{
	size_t	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	return (i);
}

size_t	PmergeMe::_findSpace(std::string const &input)
{
	size_t	space;

	space = input.find(' ');
	return (space);
}