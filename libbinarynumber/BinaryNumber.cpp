/*
	A simple decimal (long long) to binary string ("1000111") converter
	in C++ std-17.

	Author:		Dipayan Sarker
	Date:		December 03, 2020
	file:		BinaryNumber.cpp

	Version:	1.0.0.2
*/

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <limits>
#include <vector>

#include "binarynumber.h"

BinaryNumber::BinaryNumber(long long decNum)
	: m_numDecimal(decNum), m_isStrContor(false)
{
	this->processDecimalNumber();
}

BinaryNumber::BinaryNumber(std::string_view binStr)
	: m_numBinaryStr(binStr), m_numDecimal(0LL), m_isStrContor(true)
{
	this->processBinaryString();
}

BinaryNumber::BinaryNumber(BinaryNumber&& src) noexcept
{
	this->m_isStrContor = src.m_isStrContor;
	src.m_isStrContor = false;
	this->m_numBinaryStr = std::move(src.m_numBinaryStr);
	src.m_numBinaryStr.push_back('0');
	this->m_numDecimal = src.m_numDecimal;
	src.m_numDecimal = 0LL;
}

BinaryNumber& BinaryNumber::operator=(BinaryNumber&& other) noexcept
{
	if (this != &other)
	{
		this->m_isStrContor = other.m_isStrContor;
		other.m_isStrContor = false;
		this->m_numBinaryStr = std::move(other.m_numBinaryStr);
		other.m_numBinaryStr.push_back('0');
		this->m_numDecimal = other.m_numDecimal;
		other.m_numDecimal = 0LL;
	}
	return *this;
}

bool BinaryNumber::operator==(const BinaryNumber& other) const
{
	return this->m_isStrContor == other.m_isStrContor
		&& this->m_numBinaryStr.compare(other.m_numBinaryStr) == 0
		&& this->m_numDecimal == other.m_numDecimal;
}

BinaryNumber::operator std::string() const
{
	return this->m_numBinaryStr;
}

BinaryNumber::operator long long() const
{
	return this->m_numDecimal;
}

std::string_view BinaryNumber::getBinaryStr() const
{
	return std::string_view(this->m_numBinaryStr);
}

long long BinaryNumber::getDecimal() const
{
	return m_numDecimal;
}

bool BinaryNumber::isValidBinStr(std::string_view binStr)
{
	return std::all_of(binStr[0] == '-' ? binStr.begin() + 1 : binStr.begin(), binStr.end(), [](const char& c) { return c == '0' || c == '1'; });
}

bool BinaryNumber::isValidDecNum(const long long& decNum)
{
	return decNum <= std::numeric_limits<long long>::max();
}

void BinaryNumber::processBinaryString()
{
	if (this->m_isStrContor)
	{
		if (!BinaryNumber::isValidBinStr(this->m_numBinaryStr))
		{
			throw std::invalid_argument("invalid binary string!");
		}
		this->m_numDecimal = std::stoll(this->m_numBinaryStr, nullptr, 2);
	}
	else
	{
		if (!BinaryNumber::isValidDecNum(this->m_numDecimal))
		{
			throw std::invalid_argument("invalid decimal number!");
		}
	}
}

void BinaryNumber::processDecimalNumber()
{
	if (!this->m_isStrContor)
	{
		if (!BinaryNumber::isValidDecNum(this->m_numDecimal))
		{
			throw std::invalid_argument("invalid decimal number!");
		}
		char bin = 0;
		std::vector<char> charVec{};
		long long numDecCpy = this->m_numDecimal < 0 ? this->m_numDecimal * -1 : this->m_numDecimal; // make m_numDecimal positive if it is < 0
		if (this->m_numDecimal == 0)
		{
			charVec.push_back('0');
			goto EndProcess;
		}
		while (numDecCpy != 0)
		{
			bin += (numDecCpy % 2);
			charVec.push_back(static_cast<char>(bin + '0'));
			bin = 0;
			numDecCpy /= 2;
		}
	EndProcess:
		if (this->m_numDecimal < 0)
		{
			charVec.push_back('-');
		}
		std::reverse(charVec.begin(), charVec.end());
		this->m_numBinaryStr = std::string(charVec.data(), charVec.size()); // move assignment
	}
	else
	{
		if (!BinaryNumber::isValidBinStr(this->m_numBinaryStr))
		{
			throw std::invalid_argument("invalid binary string!");
		}
	}
}
