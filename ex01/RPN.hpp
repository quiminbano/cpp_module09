/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:39:53 by corellan          #+#    #+#             */
/*   Updated: 2023/08/13 21:21:12 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>

typedef	std::stack<unsigned int>	stack;

class RPN
{
private:

	std::string		_input;
	stack			_stack;
	std::string		*_parsed_input;
	unsigned int	_arguments;

	RPN(void);
	RPN(RPN const &rhs);

	RPN	&operator=(RPN const &rhs);

	std::string	*_splitcplusplus(std::string &input);
	size_t		_countWords(std::string const &input);

public:

	class	Error : public std::exception
	{
		virtual const char	*what(void) const throw();
	};

	RPN(std::string	&input);
	~RPN(void);
};

#endif