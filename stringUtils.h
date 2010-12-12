#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <sstream>

using std::string;
using std::ios_base;

namespace stringUtils
{
	string getXMLAttr(string line, string attr);
	string ASCIIToStr(string input);
	int charToInt(char a);
	//converts from a string to an arbitray numerical format
	template<class T> T fromString(const string& s, ios_base& (*f)(ios_base&) = std::hex)
	{
		std::istringstream stream(s);
		T t;
		stream >> f >> t;
		return t;
	}

	//converts to a string from an arbitrary numerical format
	template<class T> string toString(const T& t)
	{
		std::ostringstream stream;
		stream << t;
		return stream.str();
	}

}

#endif
