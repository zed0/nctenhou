#include "stringUtils.h"

string stringUtils::getXMLAttr(string line, string attr)
{
	string match = attr+"=\"";
	size_t start = line.find(match) + match.length();
	size_t end = line.find("\"",start);
	if(end != string::npos)
	{
		return line.substr(start, end-start);
	}
	else
	{
		return "";
	}
}

string stringUtils::ASCIIToStr(string input)
{
	string result = "";
	for(int i=0; i<(input.length()-2); i+=3)
	{
		string character;
		int charvalue;
		character += input.at(i+1);
		character += input.at(i+2);
		charvalue = fromString<int>(character, std::hex);
		result += char(charvalue);
	}
	return result;
}

int stringUtils::charToInt(char a)
{
	return a - '0';
}
