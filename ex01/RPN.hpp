/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:39:53 by corellan          #+#    #+#             */
/*   Updated: 2023/08/14 13:17:54 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <sstream>

typedef	std::stack<int>	stack;

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
	size_t		_countSpaceOrTab(std::string const &input);
	size_t		_findSpaceOrTab(std::string const &input);
	int			_validateInput(std::string const &input);
	int			_doOperations(void);

public:

	class	Error : public std::exception
	{
		virtual const char	*what(void) const throw();
	};

	RPN(std::string	&input);
	~RPN(void);
};

#endif