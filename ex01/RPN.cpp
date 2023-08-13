/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:34:30 by corellan          #+#    #+#             */
/*   Updated: 2023/08/13 21:35:06 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string &input) : _arguments(0), _input(input), _parsed_input(NULL)
{
	
}

RPN::~RPN(void)
{
	
}

std::string	*RPN::_splitcplusplus(std::string &input)
{
	std::string	*split;
	size_t		words;
	size_t		i;

	words = _countWords(input);
	split = NULL;
	i = 0;
	try
	{
		split = new std::string[words];
	}
	catch(const std::bad_alloc &e)
	{
		return (NULL);
	}
	_arguments = static_cast<unsigned int>(words);
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

const char	*RPN::Error::what(void) const throw()
{
	return ("Error");
}
