/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:41:17 by corellan          #+#    #+#             */
/*   Updated: 2023/08/12 17:58:51 by corellan         ###   ########.fr       */
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
	if (this->_checkFormatDatabase() == -1)
		throw (WrongFormatDatabase());
	if (this->_checkFormatFile() == -1)
		throw (WrongFormatFile());
	_processData();
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

int	BitcoinExchange::_checkFormatDatabase(void)
{
	size_t	i;

	i = 1;
	if (this->_storeDoc(this->_database, this->_database_doc, this->_lines_database) == -1)
		return (-1);
	if (this->_lines_database < 2)
		return (-1);
	this->_parsed_database = this->_parseLines(this->_database_doc, this->_lines_database);
	if (!this->_parsed_database)
		return (-1);
	if (this->_parsed_database[0].compare("date,exchange_rate"))
		return (-1);
	while (i < this->_lines_database)
	{
		if (this ->_checkLineFormatDatabase(this->_parsed_database[i]) == -1)
			return (-1);
		i++;
	}
	if (_checkDateDatabase() == -1)
		return (-1);
	return (0);
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

int	BitcoinExchange::_storeDoc(std::ifstream &file, std::string &doc, size_t &lines)
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

std::string	*BitcoinExchange::_parseLines(std::string &doc, size_t &lines)
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

int	BitcoinExchange::_checkLineFormatDatabase(std::string const &line)
{
	size_t	i;

	i = 0;
	while (std::isdigit(line[i]))
		i++;
	if (i == 0 || line[i] != '-')
		return (-1);
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] != '-')
		return (-1);
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] != ',')
		return (-1);
	i++;
	if (line[i] == 0)
		return (-1);
	while (std::isdigit(line[i]))
		i++;
	if (line[i] != 0 && line[i] != '.')
		return (-1);
	else if (line[i] == 0)
		return (0);
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (i < line.size())
		return (-1);
	return (0);
}

int	BitcoinExchange::_checkLineFormatFile(std::string const &line)
{
	size_t	i;

	i = 0;
	while (std::isdigit(line[i]))
		i++;
	if (i == 0 || line[i] != '-')
		return (-1);
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] != '-')
		return (-1);
	i++;
	while (std::isdigit(line[i]))
		i++;
	if (line[i] != ' ')
		return (-1);
	i++;
	if (line[i] != '|')
		return (-1);
	i++;
	if (line[i] != ' ')
		return (-1);
	i++;
	if (line[i] == '+' || line[i] == '-')
		i++;
	while (std::isdigit(line[i]))
		i++;
	if (i < line.size())
		return (-1);
	return (0);
}

int	BitcoinExchange::_checkDateDatabase(void)
{
	size_t			i;
	std::string		temp;
	size_t			position;
	unsigned int	year;
	unsigned int	month;
	unsigned int	day;
	float			data;

	i = 1;
	data = 0;
	while (i < _lines_database)
	{
		position = _findSpaceOrDash(_parsed_database[i]);
		temp.clear();
		temp = _parsed_database[i].substr(0, position);
		std::istringstream	iss;
		iss.str(temp);
		iss >> year;
		if (iss.fail() == true)
			return (-1);
		if (year > 2023 || year < 2009)
			return (-1);
		temp.clear();
		temp = _parsed_database[i].substr((position + 1), _findSpaceOrDash(_parsed_database[i].substr((position + 1))));
		std::istringstream	iss2;
		iss2.str(temp);
		iss2 >> month;
		if (iss.fail() == true || month > 12)
			return (-1);
		position += (_findSpaceOrDash(_parsed_database[i].substr((position + 1))) + 1);
		temp.clear();
		temp = _parsed_database[i].substr((position + 1), _findSpaceOrDash(_parsed_database[i].substr((position + 1))));
		std::istringstream	iss3;
		iss3.str(temp);
		iss3 >> day;
		if (iss.fail() == true || day > 31 || _checkYearMonthDatabase(month, day, year) == -1)
			return (-1);
		if (_parsed_database[i].find(',') == std::string::npos)
			return (-1);
		position = (_parsed_database[i].find(',') + 1);
		temp = _parsed_database[i].substr(position);
		std::istringstream	iss4;
		iss4.str(temp);
		iss4 >> data;
		if (iss4.fail() == true)
			return (-1);
		_map_database[year][month][day] = data;
		i++;
	}
	return (0);
}

size_t	BitcoinExchange::_findSpaceOrDash(std::string const &input)
{
	size_t	i;

	i = 0;
	while (input[i] && input[i] != '-' && input[i] != ' ')
		i++;
	return (i);
}

int	BitcoinExchange::_checkYearMonthDatabase(unsigned int &month, unsigned int &day, unsigned int &year)
{
	if ((month < 8 && (month % 2)) && (day > 31))
		return (-1);
	else if ((month >= 8 && !(month % 2)) && (day > 31))
		return (-1);
	else if ((month == 2 && !(year % 4)) && (day == 29))
		return (0);
	else if ((month == 2 && (day > 28)))
		return (-1);
	else if ((month < 8 && !(month % 2)) && (day > 30))
		return (-1);
	else if ((month >= 8 && (month % 2)) && (day > 30))
		return (-1);
	return (0);
}

void	BitcoinExchange::_processData(void)
{
	size_t			i;
	std::string		temp;
	size_t			position;
	unsigned int	year;
	unsigned int	month;
	unsigned int	day;
	float			data;

	i = 1;
	data = 0;
	_findMinimunDatabase();
	while (i < _lines_file)
	{
		if (this ->_checkLineFormatFile(_parsed_file[i]) == -1)
		{
			std::cout << "Error: bad input => " << _parsed_file[i] << std::endl;
			i++;
			continue ;
		}
		position = _findSpaceOrDash(_parsed_file[i]);
		temp.clear();
		temp = _parsed_file[i].substr(0, position);
		std::istringstream	iss;
		iss.str(temp);
		iss >> year;
		if (iss.fail() == true)
		{
			std::cout << "Error: bad input => " << _parsed_file[i] << std::endl;
			i++;
			continue ;
		}
		if (year < _minYear)
		{
			std::cout << "Error: bad input => " << _parsed_file[i] << std::endl;
			i++;
			continue ;
		}
		temp.clear();
		temp = _parsed_file[i].substr((position + 1), _findSpaceOrDash(_parsed_file[i].substr((position + 1))));
		std::istringstream	iss2;
		iss2.str(temp);
		iss2 >> month;
		if (iss.fail() == true || month > 12)
		{
			std::cout << "Error: bad input => " << _parsed_file[i] << std::endl;
			i++;
			continue ;
		}
		position += (_findSpaceOrDash(_parsed_file[i].substr((position + 1))) + 1);
		temp.clear();
		temp = _parsed_file[i].substr((position + 1), _findSpaceOrDash(_parsed_file[i].substr((position + 1))));
		std::istringstream	iss3;
		iss3.str(temp);
		iss3 >> day;
		if (iss.fail() == true || day > 31 || _checkYearMonthDatabase(month, day, year) == -1)
		{
			std::cout << "Error: bad input => " << _parsed_file[i] << std::endl;
			i++;
			continue ;
		}
		position += 6;
		temp.clear();
		temp = _parsed_file[i].substr(position);
		std::istringstream	iss4;
		iss4.str(temp);
		iss4 >> data;
		if (iss4.fail() == true)
		{
			std::cout << "Error: floating point number overflowed" << std::endl;
			i++;
			continue ;
		}
		if (data < static_cast<float>(0))
		{
			std::cout << "Error: not a positive number" << std::endl;
			i++;
			continue ;
		}
		if (data > static_cast<float>(1000))
		{
			std::cout << "Error: too large a number" << std::endl;
			i++;
			continue ;
		}
		/*if (_searchInDatabase(year, month, day, data) == -1)
		{
			std::cout << "Error: not possible to find in database" << std::endl;
			i++;
			continue ;
		}*/
		i++;
	}
}

void	BitcoinExchange::_findMinimunDatabase(void)
{
	map_database::iterator		it;
	submap1_database::iterator	it2;
	submap2_database::iterator	it3;
	int							flag;

	_minYear = 0;
	_minMonth = 0;
	_minDay = 0;
	flag = 0;
	it = _map_database.begin();
	while (it != _map_database.end())
	{
		if (flag == 0)
		{
			_minYear = it->first;
			flag = 1;
		}
		else
		{
			if (it->first < _minYear)
				_minYear = it->first;
		}
		it++;
	}
	it2 = _map_database[_minYear].begin();
	flag = 0;
	while (it2 != _map_database[_minYear].end())
	{
		if (flag == 0)
		{
			_minMonth = it2->first;
			flag = 1;
		}
		else
		{
			if (it2->first < _minMonth)
				_minMonth = it2->first;
		}
		it2++;
	}
	flag = 0;
	it3 = _map_database[_minYear][_minMonth].begin();
	while (it3 != _map_database[_minYear][_minMonth].end())
	{
		if (flag == 0)
		{
			_minDay = it3->first;
			flag = 1;
		}
		else
		{
			if (it3->first < _minDay)
				_minDay = it3->first;
		}
		it3++;
	}
	std::cout << "min year:" << _minYear << ". min month:" << _minMonth << ". min day:" << _minDay << std::endl;
}

const char	*BitcoinExchange::ErrorOpeningDatabase::what(void) const throw()
{
	return ("Error: could not open database.");
}

const char	*BitcoinExchange::ErrorOpeningFile::what(void) const throw()
{
	return ("Error: could not open file.");
}

const char	*BitcoinExchange::WrongFormatDatabase::what(void) const throw()
{
	return ("Error: file data.csv does not have the proper format.");
}

const char	*BitcoinExchange::WrongFormatFile::what(void) const throw()
{
	return ("Error: file passed as argument does not have the proper format.");
}