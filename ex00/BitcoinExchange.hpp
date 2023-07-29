/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:50:32 by corellan          #+#    #+#             */
/*   Updated: 2023/07/29 15:17:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <stdexcept>

class	BitcoinExchange
{
public:

	class	ErrorOpeningDatabase : public std::exception
	{
	public:

		virtual const char	*what(void) const throw();
	};
	class	ErrorOpeningFile : public std::exception
	{
	public:

		virtual const char	*what(void) const throw();
	};

	BitcoinExchange(std::string &input_file);
	~BitcoinExchange(void);

private:

	std::map<std::string, float>	_map_database;
	std::ifstream					_database;
	std::ifstream					_file;

	BitcoinExchange(void);
	BitcoinExchange(BitcoinExchange const &rhs);

	BitcoinExchange	operator=(BitcoinExchange const &rhs);
};

#endif