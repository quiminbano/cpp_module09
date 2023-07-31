/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:50:32 by corellan          #+#    #+#             */
/*   Updated: 2023/07/31 15:35:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <cstdlib>
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
	class	WrongFormatDatabase : public std::exception
	{
	public:

		virtual const char	*what(void) const throw();
	};
	class	WrongFormatFile : public std::exception
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
	int								_lines_database;
	int								_lines_file;
	std::string						_database_doc;
	std::string						_file_doc;
	std::string						*_parsed_database;
	std::string						*_parsed_file;

	BitcoinExchange(void);
	BitcoinExchange(BitcoinExchange const &rhs);

	BitcoinExchange	operator=(BitcoinExchange const &rhs);

	int				_checkFormatDatabase(void);
	int				_checkFormatFile(void);
	int				_storeDoc(std::ifstream &file, std::string &doc, int &lines);
	int				_checkLineFormatFile(std::string const &line);
	std::string		*_parseLines(std::string &doc, int &lines);
};

#endif