/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:53:42 by corellan          #+#    #+#             */
/*   Updated: 2023/08/17 10:44:35 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <deque>
# include <vector>
# include <string>
# include <stdexcept>
# include <iostream>
# include <sstream>
# include <ctime>

typedef std::deque<unsigned int>	deque;
typedef std::vector<unsigned int>	vector;
typedef	std::vector<std::string>	str_vector;

class PmergeMe
{
private:

	deque				_deque;
	vector				_vector;
	size_t				_timeVectorInit;
	size_t				_timeVectorLast;
	size_t				_timeDequeInit;
	size_t				_timeDequeLast;
	size_t				_timeProcessInit;
	size_t				_timeProcessLast;
	static unsigned int	_nb;

	PmergeMe(PmergeMe const &rhs);
	
	PmergeMe	&operator=(PmergeMe const &rhs);

	int			_fillContainers(char **av);
	str_vector	_countArgument(char **av);
	size_t		_countWords(std::string const &input);
	str_vector	_splitcplusplus(std::string &input);
	size_t		_countSpace(std::string const &input);
	size_t		_findSpace(std::string const &input);
	int			_checkRepeated(void);
	void		_doAlgorithm(vector &container, size_t left, size_t right);
	void		_doAlgorithm(deque &container, size_t left, size_t right);
	void		_merge(vector &container, size_t left, size_t middle, size_t right);
	void		_merge(deque &container, size_t left, size_t middle, size_t right);
	void		_doInsertion(vector &container, size_t left, size_t right);
	void		_doInsertion(deque &container, size_t left, size_t right);

public:

	class Error : public std::exception
	{
		virtual const char	*what(void) const throw();
	};

	PmergeMe(void);
	~PmergeMe(void);

	void	initialize(char **av);

};

#endif