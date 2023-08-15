/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:53:42 by corellan          #+#    #+#             */
/*   Updated: 2023/08/15 19:15:32 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>
# include <string>
# include <stdexcept>
# include <iostream>

typedef std::deque<unsigned int>	deque;
typedef std::vector<unsigned int>	vector;
typedef	std::vector<std::string>	str_vector;

class PmergeMe
{
private:

	deque	_deque;
	vector	_vector;

	PmergeMe(void);
	PmergeMe(PmergeMe const &rhs);
	
	PmergeMe	&operator=(PmergeMe const &rhs);

	int			_fillContainers(char **av);
	str_vector	_countArgument(char **av);
	size_t		_countWords(std::string const &input);
	str_vector	_splitcplusplus(std::string &input);

public:

	class Error : public std::exception
	{
		virtual const char	*what(void) const throw();
	};

	PmergeMe(char **argv);
	~PmergeMe(void);

};

#endif