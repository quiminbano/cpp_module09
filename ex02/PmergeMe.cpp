/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:24:57 by corellan          #+#    #+#             */
/*   Updated: 2023/08/17 10:45:01 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

void	PmergeMe::initialize(char **av)
{
	_timeProcessInit = clock();
	if (_fillContainers(av) == -1)
		throw (Error());
	if (_checkRepeated() == -1)
		throw (Error());
	_timeProcessLast = clock();
	std::cout << "Before:               ";
	for (vector::iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << (*it) << " ";
	_timeVectorInit = clock();
	_doAlgorithm(_vector, 0, ((_vector.size() - 1)));
	_timeVectorLast = clock();
	_timeDequeInit = clock();
	_doAlgorithm(_deque, 0, ((_deque.size() - 1)));
	_timeDequeLast = clock();
	std::cout << std::endl;
	std::cout << "After (std::vector):  ";
	for (vector::iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << (*it) << " ";
	std::cout << std::endl;
	std::cout << "After (std::deque):   ";
	for (deque::iterator it = _deque.begin(); it != _deque.end(); it++)
		std::cout << (*it) << " ";
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vector.size() << " elements with std::vector : ";
	std::cout << (((static_cast<double>(_timeVectorLast - _timeVectorInit)) / CLOCKS_PER_SEC) * static_cast<double>(1000)) << " ms" << std::endl;
	std::cout << "Time to process a range of " << _deque.size() << " elements with std::deque : ";
	std::cout << (((static_cast<double>(_timeDequeLast - _timeDequeInit)) / CLOCKS_PER_SEC) * static_cast<double>(1000)) << " ms" << std::endl;
	std::cout << "Time to process the data passed as input : ";
	std::cout << (((static_cast<double>(_timeProcessLast - _timeProcessInit)) / CLOCKS_PER_SEC) * static_cast<double>(1000)) << " ms" << std::endl;
	return ;
}

int	PmergeMe::_fillContainers(char **av)
{
	str_vector				arrStr;
	str_vector				defStr;
	str_vector				tempStr;
	std::istringstream		iss;
	str_vector::iterator	it;
	unsigned int			temp;

	arrStr = _countArgument(av);
	it = arrStr.begin();
	while (it != arrStr.end())
	{
		if (_countWords((*it)) == 0)
			return (-1);
		else if (_countWords((*it)) == 1)
			defStr.push_back((*it));
		else
		{
			tempStr.clear();
			tempStr = _splitcplusplus((*it));
			for (str_vector::iterator temp_it = tempStr.begin(); temp_it != tempStr.end(); temp_it++)
				defStr.push_back((*temp_it));
		}
		it++;
	}
	tempStr.clear();
	arrStr.clear();
	it = defStr.begin();
	while (it != defStr.end())
	{
		iss.clear();
		iss.str((*it));
		iss >> temp;
		if (iss.fail() == true)
			return (-1);
		_vector.push_back(temp);
		_deque.push_back(temp);
		it++;
	}
	return (0);
}

str_vector	PmergeMe::_countArgument(char **av)
{
	size_t		i;
	str_vector	temp;

	i = 1;
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
		split.push_back(input.substr(0, _findSpace(input)));
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

int	PmergeMe::_checkRepeated(void)
{
	deque::iterator		it_deque;
	vector::iterator	it_vector;
	size_t				counter;

	it_deque = _deque.begin();
	while (it_deque != _deque.end())
	{
		it_vector = _vector.begin();
		counter = 0;
		while (it_vector != _vector.end())
		{
			if ((*it_deque) == (*it_vector))
				counter++;
			if (counter > 1)
				return (-1);
			it_vector++;
		}
		it_deque++;
	}
	return (0);
}

void	PmergeMe::_doAlgorithm(vector &container, size_t left, size_t right)
{
	size_t	middle;

	middle = 0;
	if ((right - left) > _nb)
	{
		middle = (left + ((right - left) / 2));
		_doAlgorithm(container, left, middle);
		_doAlgorithm(container, (middle + 1), right);
		_merge(container, left, middle, right);
	}
	else
		_doInsertion(container, left, right);
	return ;
}

void	PmergeMe::_doAlgorithm(deque &container, size_t left, size_t right)
{
	size_t	middle;

	middle = 0;
	if ((right - left) > _nb)
	{
		middle = (left + ((right - left) / 2));
		_doAlgorithm(container, left, middle);
		_doAlgorithm(container, (middle + 1), right);
		_merge(container, left, middle, right);
	}
	else
		_doInsertion(container, left, right);
	return ;
}

void	PmergeMe::_merge(vector &container, size_t left, size_t middle, size_t right)
{
	size_t	n1;
	size_t	n2;
	size_t	idxL;
	size_t	idxR;
	size_t	i;

	vector	tempLeft(container.begin() + left, (container.begin() + middle + 1));
	vector	tempRight((container.begin() + middle + 1), (container.begin() + right + 1));
	n1 = (middle - left + 1);
	n2 = (right - middle);
	idxL = 0;
	idxR = 0;
	for (i = left; (idxL < n1 && idxR < n2); i++)
	{
		if (tempLeft[idxL] > tempRight[idxR])
		{
			container[i] = tempRight[idxR];
			idxR++;
		}
		else
		{
			container[i] = tempLeft[idxL];
			idxL++;
		}
	}
	while (idxL < n1)
	{
		container[i] = tempLeft[idxL];
		idxL++;
		i++;
	}
	while (idxR < n2)
	{
		container[i] = tempRight[idxR];
		idxR++;
		i++;
	}	
	return ;
}

void	PmergeMe::_merge(deque &container, size_t left, size_t middle, size_t right)
{
	size_t	n1;
	size_t	n2;
	size_t	idxL;
	size_t	idxR;
	size_t	i;

	deque	tempLeft(container.begin() + left, (container.begin() + middle + 1));
	deque	tempRight((container.begin() + middle + 1), (container.begin() + right + 1));
	n1 = (middle - left + 1);
	n2 = (right - middle);
	idxL = 0;
	idxR = 0;
	for (i = left; (idxL < n1 && idxR < n2); i++)
	{
		if (tempLeft[idxL] > tempRight[idxR])
		{
			container[i] = tempRight[idxR];
			idxR++;
		}
		else
		{
			container[i] = tempLeft[idxL];
			idxL++;
		}
	}
	while (idxL < n1)
	{
		container[i] = tempLeft[idxL];
		idxL++;
		i++;
	}
	while (idxR < n2)
	{
		container[i] = tempRight[idxR];
		idxR++;
		i++;
	}	
	return ;
}

void	PmergeMe::_doInsertion(vector &container, size_t left, size_t right)
{
	size_t			i;
	size_t			j;
	unsigned int	current;

	i = left;
	while (i < right)
	{
		current = container[i + 1];
		j = (i + 1);
		while ((j > left) && (container[j - 1] > current))
		{
			container[j] = container[j - 1];
			j--;
		}
		container[j] = current;
		i++;
	}
	return ;
}

void	PmergeMe::_doInsertion(deque &container, size_t left, size_t right)
{
	size_t			i;
	size_t			j;
	unsigned int	current;

	i = left;
	while (i < right)
	{
		current = container[i + 1];
		j = (i + 1);
		while ((j > left) && (container[j - 1] > current))
		{
			container[j] = container[j - 1];
			j--;
		}
		container[j] = current;
		i++;
	}
	return ;
}

const char	*PmergeMe::Error::what(void) const throw()
{
	return ("Error");
}

unsigned int	PmergeMe::_nb = 5;
