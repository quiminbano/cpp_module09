/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:41:17 by corellan          #+#    #+#             */
/*   Updated: 2023/07/30 22:12:07 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange(std::string &input_file)
{
	this->_parsed_database = NULL;
	this->_parsed_file = NULL;
	this->_database.open("data.csv", std::ifstream::in);
	if (this->_database.fail() == true)
		throw (ErrorOpeningDatabase());
	this->_file.open(input_file, std::ifstream::in);
	if (this->_file.fail() == true)
		throw (ErrorOpeningFile());
	/*if (this->_checkFormatDatabase() == -1)
		throw (WrongFormatDatabase());*/
	if (this->_checkFormatFile() == -1)
		throw (WrongFormatFile());
	return ;
}

BitcoinExchange::~BitcoinExchange(void)
{
	this->_database.close();
	this->_file.close();
	if (this->_parsed_database)
		delete [] this->_parsed_database;
	if (this->_parsed_file)
		delete [] this->_parsed_file;
	return ;
}

int	BitcoinExchange::_checkFormatFile(void)
{
	if (this->_storeDoc(this->_file, this->_file_doc, this->_lines_file) == -1)
		return (-1);
	if (this->_lines_file < 2)
		return (-1);
	this->_parsed_file = this->_parseLines(this->_file_doc, this->_lines_file);
	if (!this->_parsed_file)
		return (-1);
	if (this->_parsed_file[0].compare("date | value"))
		return (-1);
	return (0);
}

int	BitcoinExchange::_storeDoc(std::ifstream &file, std::string &doc, int &lines)
{
	std::string	temp;
	int			flag;

	flag = 0;
	lines = 0;
	while(std::getline(file, temp))
	{
		if (flag == 0)
		{
			doc = temp;
			flag = 1;
		}
		else
			doc += temp;
		lines++;
		doc += '\n';
		file.sync();
	}
	if (file.eof() == true)
		return (0);
	else if (file.fail() == true)
		return (-1);
	return (0);
}

std::string	*BitcoinExchange::_parseLines(std::string &doc, int &lines)
{
	int			i;
	int			pos;
	std::string	temp;
	std::string	*ptr;

	i = 0;
	pos = 0;
	temp = doc;
	try
	{
		ptr = new std::string[lines];
	}
	catch(const std::exception& e)
	{
		return (NULL);
	}
	while (temp.find('\n') != std::string::npos)
	{
		pos = temp.find('\n');
		ptr[i] = temp.substr(0, pos);
		i++;
		temp = temp.substr(pos + 1);
	}
	return (ptr);
}

const char	*BitcoinExchange::ErrorOpeningDatabase::what(void) const throw()
{
	return ("Error: data.csv is not present in this directory or it could not be opened.");
}

const char	*BitcoinExchange::ErrorOpeningFile::what(void) const throw()
{
	return ("Error: there was a problem trying to open the file provided as argument.");
}

const char	*BitcoinExchange::WrongFormatDatabase::what(void) const throw()
{
	return ("Error: file data.csv does not have the proper format.");
}

const char	*BitcoinExchange::WrongFormatFile::what(void) const throw()
{
	return ("Error: file passed as argument does not have the proper format.");
}