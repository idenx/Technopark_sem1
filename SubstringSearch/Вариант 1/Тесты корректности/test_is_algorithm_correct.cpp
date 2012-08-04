#include <string>
#include <vector>
#include <wtypes.h>
#include <iostream>
#include <iterator>

void CalculatePrefixFunction(const std::string& string, std::vector<size_t>& prefixes);
void PrintFindedPositions(const std::vector<size_t>& positions);
void ReadStrings(std::string& string, std::string& subtring);
void SearchSubstringSimple(const std::string& string, const std::string& substring, std::vector<size_t>& findedPositions);
void SearchSubstringByKMP(const std::string& string, const std::string& substring, std::vector<size_t>& findedPositions);

int main()
{
	std::string string, substring;
	ReadStrings(string, substring);
	std::vector<size_t> findedPositionsKMP, findedPositionsSimple;
	SearchSubstringSimple(string, substring, findedPositionsSimple);
	SearchSubstringByKMP(string, substring, findedPositionsKMP);
	if (findedPositionsKMP == findedPositionsSimple)
	{
		std::cout << "GOOD ";
	}
	else
	{
		std::cout << "BAD ";
	}
	std::cout << findedPositionsKMP.size() << " " << findedPositionsSimple.size() << std::endl;
	std::system("PAUSE");
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

void CalculatePrefixFunction(const std::string& string, std::vector<size_t>& prefixes) {
	size_t stringLength = string.length(); 
	prefixes[0] = 0; 

	size_t currentPrefix = 0;
	for(size_t stringPosition = 1; stringPosition < stringLength; ++stringPosition) {          
		while ((currentPrefix > 0) && (string[currentPrefix] != string[stringPosition]) ) 
			currentPrefix = prefixes[currentPrefix-1]; 
		if (string[currentPrefix] == string[stringPosition])
			++currentPrefix;
		prefixes[stringPosition] = currentPrefix;
	}
}

void SearchSubstringSimple(const std::string& string, const std::string& substring, std::vector<size_t>& findedPositions)
{
	size_t inputedStringLength = string.length();
	size_t substringLength = substring.length();
	size_t matchedSymbols;

	for(size_t stringPosition = 0; stringPosition < inputedStringLength - substringLength + 1; ++stringPosition) {
		matchedSymbols = 0;
		for(size_t substringPosition = 0; substringPosition < substringLength; ++substringPosition) {
			if(string[stringPosition + substringPosition] == substring[substringPosition])
				++matchedSymbols;
			else
				break;
		}
		if(matchedSymbols == substringLength) {
			findedPositions.push_back(stringPosition);
		}
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