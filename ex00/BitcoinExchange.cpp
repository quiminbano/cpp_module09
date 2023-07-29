/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:41:17 by corellan          #+#    #+#             */
/*   Updated: 2023/07/29 15:32:31 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string &input_file)
{
	this->_database.open("data.csv", std::ifstream::in);
	if (this->_database.fail() == true)
		throw (ErrorOpeningDatabase());
	this->_file.open(input_file, std::ifstream::in);
	if (this->_file.fail() == true)
		throw (ErrorOpeningFile());
	return ;
}

BitcoinExchange::~BitcoinExchange(void)
{
	this->_database.close();
	this->_file.close();
	return ;
}

const char	*BitcoinExchange::ErrorOpeningDatabase::what(void) const throw()
{
	return ("Error: data.csv is not present in this directory or it could not be opened.");
}

const char	*BitcoinExchange::ErrorOpeningFile::what(void) const throw()
{
	return ("Error: there was a problem trying to open the file provided as argument.");
}