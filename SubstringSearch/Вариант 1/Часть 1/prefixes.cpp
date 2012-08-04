#include <string>
#include <vector>
#include <wtypes.h>
#include <iostream>
#include <iterator>

void CalculatePrefixFunction(const std::string& string, std::vector<size_t>& prefixes);
void PrintPrefixes(const std::vector<size_t>& prefixes);
void ReadString(std::string& substring);

int main()
{
	std::string substring;
	ReadString(substring);
	std::vector<size_t> prefixes(substring.length());
	CalculatePrefixFunction(substring, prefixes);
	PrintPrefixes(prefixes);
	return 0;
}

void PrintPrefixes(const std::vector<size_t>& prefixes)
{
	copy(prefixes.begin(), prefixes.end(), std::ostream_iterator<size_t>(std::cout, " "));
}

void ReadString(std::string& substring)
{
	std::cin >> substring;
}

void CalculatePrefixFunction(const std::string& string, std::vector<size_t>& prefixes)
{
	size_t stringLength = string.length(); 
	prefixes[0] = 0; 

	size_t currentPrefix = 0;
	for(size_t stringPosition = 1; stringPosition < stringLength; ++stringPosition)
	{          
		while ((currentPrefix > 0) && (string[currentPrefix] != string[stringPosition]) ) 
			currentPrefix = prefixes[currentPrefix-1]; 
		if (string[currentPrefix] == string[stringPosition])
			++currentPrefix;
		prefixes[stringPosition] = currentPrefix;
	}
}