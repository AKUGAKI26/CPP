#include "ScalarConverter.hpp"

#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

namespace
{
	enum LiteralType
	{
		CHAR_LITERAL,
		INT_LITERAL,
		FLOAT_LITERAL,
		DOUBLE_LITERAL,
		INVALID_LITERAL
	};

	bool isSpecial(const std::string& literal)
	{
		return literal == "-inff" || literal == "+inff" || literal == "nanf"
			|| literal == "-inf" || literal == "+inf" || literal == "nan";
	}

	LiteralType detectType(const std::string& literal)
	{
		if (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'')
			return CHAR_LITERAL;
		if (isSpecial(literal))
			return literal[literal.size() - 1] == 'f' ? FLOAT_LITERAL : DOUBLE_LITERAL;

		char* end = 0;
		errno = 0;
		std::strtol(literal.c_str(), &end, 10);
		if (errno == 0 && *end == '\0')
			return INT_LITERAL;

		errno = 0;
		std::strtod(literal.c_str(), &end);
		if (errno == 0 && *end == '\0')
			return DOUBLE_LITERAL;
		if (literal.size() > 1 && literal[literal.size() - 1] == 'f')
		{
			std::string withoutSuffix = literal.substr(0, literal.size() - 1);
			errno = 0;
			std::strtod(withoutSuffix.c_str(), &end);
			if (errno == 0 && *end == '\0')
				return FLOAT_LITERAL;
		}
		return INVALID_LITERAL;
	}

	bool parseNumber(const std::string& literal, LiteralType type, double& value)
	{
		if (literal == "nan" || literal == "nanf")
		{
			value = std::numeric_limits<double>::quiet_NaN();
			return true;
		}
		if (literal == "+inf" || literal == "+inff")
		{
			value = std::numeric_limits<double>::infinity();
			return true;
		}
		if (literal == "-inf" || literal == "-inff")
		{
			value = -std::numeric_limits<double>::infinity();
			return true;
		}
		std::string input = literal;
		if (type == FLOAT_LITERAL && !isSpecial(literal))
			input.erase(input.size() - 1);
		char* end = 0;
		errno = 0;
		value = std::strtod(input.c_str(), &end);
		return errno != ERANGE && *end == '\0';
	}

	bool isNan(double value)
	{
		return value != value;
	}

	bool isInfinite(double value)
	{
		return !isNan(value)
			&& (value == std::numeric_limits<double>::infinity()
				|| value == -std::numeric_limits<double>::infinity());
	}

	void printChar(double value)
	{
		if (isNan(value) || isInfinite(value)
			|| value < std::numeric_limits<char>::min()
			|| value > std::numeric_limits<char>::max())
			std::cout << "char: impossible\n";
		else if (value < 32 || value > 126)
			std::cout << "char: Non displayable\n";
		else
			std::cout << "char: '" << static_cast<char>(value) << "'\n";
	}

	void printInt(double value)
	{
		if (isNan(value) || isInfinite(value)
			|| value < std::numeric_limits<int>::min()
			|| value > std::numeric_limits<int>::max())
			std::cout << "int: impossible\n";
		else
			std::cout << "int: " << static_cast<int>(value) << "\n";
	}

	void printFloat(double value)
	{
		std::cout << "float: ";
		if (isNan(value))
			std::cout << "nanf\n";
		else if (value == std::numeric_limits<double>::infinity())
			std::cout << "+inff\n";
		else if (value == -std::numeric_limits<double>::infinity())
			std::cout << "-inff\n";
		else if (value > std::numeric_limits<float>::max()
			|| value < -std::numeric_limits<float>::max())
			std::cout << "impossible\n";
		else
			std::cout << std::fixed << std::setprecision(1)
				<< static_cast<float>(value) << "f\n";
	}

	void printDouble(double value)
	{
		std::cout << "double: ";
		if (isNan(value))
			std::cout << "nan\n";
		else if (value == std::numeric_limits<double>::infinity())
			std::cout << "+inf\n";
		else if (value == -std::numeric_limits<double>::infinity())
			std::cout << "-inf\n";
		else
			std::cout << std::fixed << std::setprecision(1) << value << "\n";
	}
}

void ScalarConverter::convert(const std::string& literal)
{
	LiteralType type = detectType(literal);
	if (type == INVALID_LITERAL)
	{
		std::cout << "char: impossible\nint: impossible\n"
			<< "float: impossible\ndouble: impossible\n";
		return;
	}

	double value = 0;
	if (type == CHAR_LITERAL)
		value = static_cast<double>(literal[1]);
	else if (!parseNumber(literal, type, value))
	{
		std::cout << "char: impossible\nint: impossible\n"
			<< "float: impossible\ndouble: impossible\n";
		return;
	}
	printChar(value);
	printInt(value);
	printFloat(value);
	printDouble(value);
}
