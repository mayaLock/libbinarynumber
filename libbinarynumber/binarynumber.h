/*
	A simple decimal (long long) to binary string ("1000111") converter
	in C++ std-17. 
	
	Author:		Dipayan Sarker
	Date:		December 03, 2020
	file:		binarynumber.h

	Version:	1.0.0.2
*/


#ifndef _BINARY_NUMBER_H_
#define _BINARY_NUMBER_H_

#include <string>
#include <string_view>
#include <ostream>

constexpr std::string_view LIB_BIN_STR_VERSION("1.0.0.2");

/// <summary>
/// converts decimal to binary and vice-versa
/// </summary>
class BinaryNumber
{
public:
	BinaryNumber() = delete;
	/// <summary>
	/// explicit constructor
	/// </summary>
	/// <param name="decNum">decimal number max range LLMAX</param>
	/// <exception cref="std::invalid_argument"></exception>
	explicit BinaryNumber(long long decNum);
	/// <summary>
	/// explicit constructor
	/// </summary>
	/// <param name="binStr">valid binary string e.g. "010011"</param>
	/// <exception cref="std::invalid_argument"></exception>
	explicit BinaryNumber(std::string_view binStr);
	BinaryNumber(const BinaryNumber& src) = default;
	BinaryNumber(BinaryNumber&& src) noexcept;
	virtual ~BinaryNumber() = default;
	BinaryNumber& operator=(const BinaryNumber& other) = default;
	BinaryNumber& operator=(BinaryNumber&& other) noexcept;
	virtual bool operator==(const BinaryNumber& other) const;
	virtual operator std::string() const;
	virtual operator long long() const;
public:
	/// <summary>
	/// gets string representation of BinaryNumber
	/// </summary>
	/// <returns>std::string_view</returns>
	std::string_view getBinaryStr() const;
	/// <summary>
	/// gets decimal representation of BinaryNumber
	/// </summary>
	/// <returns>long long</returns>
	long long getDecimal() const;
public:
	/// <summary>
	/// ckecks if given string is a vaild binary string or not
	/// </summary>
	/// <param name="binStr">binary string</param>
	/// <returns>bool</returns>
	static bool isValidBinStr(std::string_view binStr);
	/// <summary>
	/// ckecks if given decimal is a vaild long long or not
	/// </summary>
	/// <param name="decNum">decimal long long number</param>
	/// <returns>bool</returns>
	static bool isValidDecNum(const long long& decNum);
protected:
	/// <summary>
	/// decides how binary string should be converted to decimal (long long)
	/// </summary>
	/// <exception cref="std::invalid_argument"></exception>
	virtual void processBinaryString();
	/// <summary>
	/// decides how decimal (long long) should be converted to binary string 
	/// </summary>
	/// <exception cref="std::invalid_argument"></exception>
	virtual void processDecimalNumber();
protected:
	long long m_numDecimal;
	std::string m_numBinaryStr;
	bool m_isStrContor;
};

inline std::ostream& operator<<(std::ostream& os, const BinaryNumber& bn)
{
	os << static_cast<std::string>(bn);
	return os;
}

#endif // !_BINARY_NUMBER_H_
