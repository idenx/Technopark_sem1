#include <string>
#include <vector>
#include <wtypes.h>
#include <iostream>
#include <iterator>

void CalculatePrefixFunction(const std::string& string, std::vector<size_t>& prefixes);
void PrintFindedPositions(const std::vector<size_t>& positions);
void ReadStrings(std::string& string, std::string& subtring);
void SearchSubstringByKMP(const std::string& string, const std::string& substring, std::vector<size_t>& findedPositions);

int main()
{
	std::string string, substring;
	ReadStrings(string, substring);
	std::vector<size_t> findedPositions;
	SearchSubstringByKMP(string, substring, findedPositions);
	PrintFindedPositions(findedPositions);
	return 0;
}

void PrintFindedPositions(const std::vector<size_t>& positions)
{
	std::cout << positions.size() << std::endl;
	copy(positions.begin(), positions.end(), std::ostream_iterator<size_t>(std::cout, " "));
}

void ReadStrings(std::string& string, std::string& substring)
{
	std::cin >> substring;
	std::cin >> string;
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

void SearchSubstringByKMP(const std::string& string, const std::string& substring, std::vector<size_t>& findedPositions)
{
	size_t stringLength = string.length();
	size_t substringLength = substring.length();
	size_t matchedSymbols = 0;
	std::vector<size_t> prefixes(stringLength);
	CalculatePrefixFunction(substring, prefixes);
	for(size_t stringPosition = 0; stringPosition < stringLength; ++stringPosition)
	{
		while(matchedSymbols > 0 && substring[matchedSymbols] != string[stringPosition]) 
		{
			matchedSymbols = prefixes[matchedSymbols - 1];
		}
		if(substring[matchedSymbols] == string[stringPosition])
		{
			++matchedSymbols;
		}
		if(matchedSymbols == substringLength)
		{
			findedPositions.push_back(stringPosition - matchedSymbols + 1);
			matchedSymbols = prefixes[matchedSymbols - 1];
		}
	}
}