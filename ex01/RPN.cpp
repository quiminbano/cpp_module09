/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:34:30 by corellan          #+#    #+#             */
/*   Updated: 2023/08/17 10:33:27 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void) : _parsed_input(NULL), _arguments(0)
{
	return ;
}

RPN::~RPN(void)
{
	if (_parsed_input)
		delete [] _parsed_input;
	return ;
}

void	RPN::initialize(std::string &input)
{
	size_t	i;

	i = 0;
	_input = input;
	_parsed_input = _splitcplusplus(input);
	if (!_parsed_input)
		throw (Error());
	while (i < _arguments)
	{
		if (_validateInput(_parsed_input[i]) == -1)
			throw(Error());
		i++;
	}
	if (_doOperations() == -1)
		throw(Error());
	return ;
}

std::string	*RPN::_splitcplusplus(std::string &input)
{
	std::string	*split;
	size_t		words;
	size_t		i;

	words = _countWords(input);
	split = NULL;
	i = 0;
	if (words < 3)
		return (split);
	try
	{
		split = new std::string[words];
	}
	catch(const std::bad_alloc &e)
	{
		return (NULL);
	}
	_arguments = static_cast<unsigned int>(words);
	while (i < words)
	{
		input = input.substr(_countSpaceOrTab(input));
		split[i] = input.substr(0, _findSpaceOrTab(input));
		if ((i + 1) < words)
			input = input.substr(_findSpaceOrTab(input) + _countSpaceOrTab(input.substr(_findSpaceOrTab(input))));
		i++;
	}
	return (split);
}

size_t	RPN::_countWords(std::string const &input)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] != '\t' && input[i] != ' ' ) && 
			(input[i + 1] == '\t' || input[i + 1] == ' ' || input[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

size_t	RPN::_countSpaceOrTab(std::string const &input)
{
	size_t	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	return (i);
}

size_t	RPN::_findSpaceOrTab(std::string const &input)
{
	size_t	space;
	size_t	tab;

	space = input.find(' ');
	tab = input.find('\t');
	if (space <= tab)
		return (space);
	return (tab);
}

int	RPN::_validateInput(std::string const &input)
{
	size_t			i;
	unsigned int	temp;

	i = 0;
	if (std::isdigit(input[0]))
	{
		while (std::isdigit(input[i]))
			i++;
		if (i < input.size())
			return (-1);
		else if (i > 2)
			return (-1);
		std::istringstream	iss;
		iss.str(input);
		iss >> temp;
		if ((iss.fail() == true) || temp >= 10)
			return (-1);
	}
	else
	{
		if (input.size() > 1)
			return (-1);
		else if (input[0] != '+' && input[0] != '-' && input[0] != '*' && input[0] != '/')
			return (-1);
	}
	return (0);
}

int	RPN::_doOperations(void)
{
	size_t	i;
	int		temp;
	int		num1;
	int		num2;
	int		result;

	i = 0;
	while (i < _arguments)
	{
		num1 = 0;
		num2 = 0;
		result = 0;
		temp = 0;
		if (std::isdigit(_parsed_input[i][0]))
		{
			std::istringstream	iss;
			iss.str(_parsed_input[i]);
			iss >> temp;
			if (iss.fail() == true)
				return (-1);
			_stack.push(temp);
		}
		else
		{
			if (_stack.size() < 2)
				return (-1);
			num2 = _stack.top();
			_stack.pop();
			num1 = _stack.top();
			_stack.pop();
			if (!_parsed_input[i].compare("+"))
				result = (num1 + num2);
			else if (!_parsed_input[i].compare("-"))
				result = (num1 - num2);
			else if (!_parsed_input[i].compare("*"))
				result = (num1 * num2);
			else
			{
				if (num2 == 0)
					return (-1);
				result = (num1 / num2);
			}
			_stack.push(result);
		}
		i++;
	}
	if (_stack.size() > 1)
		return (-1);
	std::cout << _stack.top() << std::endl;
	return (0);
}

const char	*RPN::Error::what(void) const throw()
{
	return ("Error");
}
