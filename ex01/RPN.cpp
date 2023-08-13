/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:34:30 by corellan          #+#    #+#             */
/*   Updated: 2023/08/13 11:36:59 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string &input) : _arguments(0), _input(input), _parsed_input(NULL)
{
	
}

RPN::~RPN(void)
{
	
}

const char	*RPN::Error::what(void) const throw()
{
	return ("Error");
}
