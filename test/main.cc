#include <iostream>
#include <utility>

#include "../libbinarynumber/binarynumber.h"

#pragma comment(lib, "libbinarynumber.lib")

int main(int argc, char* argv[])
{
	BinaryNumber b1(1024);
	std::cout << b1 << '\n';
	std::cout << static_cast<long long>(b1) << '\n';

	BinaryNumber* n = new BinaryNumber(b1);

	BinaryNumber* n2 = new BinaryNumber(std::move(*n));

	*n = b1;

	std::cout << "n > " << static_cast<long long>(*n) << '\n';
	std::cout << "n2 > " << static_cast<long long>(*n2) << '\n';

	*n = BinaryNumber(-5); // move assignment
	std::cout << "n again > " << static_cast<std::string>(*n) << '\n';

	delete n;
	delete n2;
	
	BinaryNumber b2(b1);
	std::cout << (b1 == b2) << '\n';

	//BinaryNumber b3("012121521"); // throws std::invalid_argument exception since it is not a valid binary string

	BinaryNumber b4("01110011");
	std::cout << b4.getDecimal() << '\n';

	//b4 = b1; // copy assignment 

	b4 = std::move(b1); // move assignment


	std::cout << static_cast<long long>(b4) << '\n';
	std::cout << b4.getBinaryStr() << '\n';
	std::cout << b1 << '\n';

	BinaryNumber b5("11");

	b1 = std::move(b5);
	std::cout << b1.getDecimal() << '\n';

	std::cin.get();
	return 0;
}