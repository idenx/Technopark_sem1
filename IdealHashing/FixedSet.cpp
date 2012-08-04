#include "stdafx.h"
#include <iostream>
#include <vector>
#include <assert.h>

template<class ValueType>
class FixedSet;

inline void InputNumbers(std::vector<int>& numbersArray);
inline void ProcessRequests(const FixedSet<int>& fixedSet, const std::vector<int>& requestsArray, std::vector<bool>& requestResults);
inline void OutputResults(const std::vector<bool>& requestResults);

const int EMPTY_VALUE = 0x7FFFFFFF;
const int BIG_PRIME_NUMBER = 1610612741;

template<class ValueType>
inline size_t hashFunctionLevel2(size_t offset, const ValueType& value, size_t hashTableSize);

template<class ValueType>
inline size_t hashFunctionLevel1(const ValueType& value, size_t hashTableSize);

template<class ValueType>
inline void PushToHashTable(std::vector<ValueType>& secondLevelHash, const ValueType& value);

template<class ValueType>
class FixedSet
{
private:
	typedef std::vector<ValueType> vecType;

	std::vector<vecType> hashArray;
	size_t bucketsCount;

public:
	FixedSet();
	FixedSet(const vecType& values);
	bool Contains(ValueType value) const;
};



template<class ValueType>
FixedSet<ValueType>::FixedSet(const vecType& values)
{

	bucketsCount = values.size();
	assert(bucketsCount != 0);
	hashArray.resize(bucketsCount);

	// Distribute values on the first level
	for (vecType::const_iterator iterator = values.begin(); iterator != values.end(); ++iterator)
	{
		hashArray[hashFunctionLevel1(*iterator, bucketsCount)].push_back(*iterator);
	}

	// Distribute values on the second level
	for (std::vector<vecType>::iterator currentBucket = hashArray.begin(); currentBucket != hashArray.end(); ++currentBucket)
	{
		// (Nj)^2 values on the second level
		if (currentBucket->size() != 0)
		{
			vecType hashTableOfSecondLevel(currentBucket->size() * currentBucket->size(), EMPTY_VALUE);
			for (vecType::const_iterator currentValue = currentBucket->begin(); currentValue != currentBucket->end(); ++currentValue)
			{
				PushToHashTable(hashTableOfSecondLevel, *currentValue);
			}
			currentBucket->swap(hashTableOfSecondLevel);
		}
	}
}

template<class ValueType>
inline void PushToHashTable(std::vector<ValueType>& hashTable, const ValueType& value)
{
	size_t hashTableSize =  hashTable.size();

	// Double hashing
	size_t currentPosition = hashFunctionLevel2(0, value, hashTableSize);
	size_t currentOffset = 0;
	while (hashTable[currentPosition] != EMPTY_VALUE && hashTable[currentPosition] != value)
	{
		currentPosition = hashFunctionLevel2(currentOffset++, value, hashTableSize);
	}
	hashTable[currentPosition] = value;
}

template<class ValueType>
inline size_t hashFunctionLevel2(size_t offset, const ValueType& value, size_t hashTableSize)
{
	assert(hashTableSize != 0);
	if (hashTableSize == 1)
		return 0;
	return (((25165843 * value + 786433) % BIG_PRIME_NUMBER) % hashTableSize + offset * ((int)(sqrt(hashTableSize)) + 1)) % hashTableSize;
}

template<class ValueType>
bool FixedSet<ValueType>::Contains(ValueType value) const
{
	size_t hashTableSize =  hashArray.size();
	size_t currentBucket = hashFunctionLevel1(value, hashTableSize);
	hashTableSize = hashArray[currentBucket].size();
	if (hashTableSize == 0)
		return false;
	size_t currentOffset = 0;
	size_t currentPosition = hashFunctionLevel2(currentOffset++, value, hashTableSize);
	ValueType currentValue = hashArray[currentBucket][currentPosition];
	while (currentValue != EMPTY_VALUE && currentOffset <= hashTableSize)
	{
		if (currentValue == value)
		{
			return true;
		}
		else
		{
			if (hashTableSize == 1)
				return false;
			currentPosition = hashFunctionLevel2(currentOffset++, value, hashTableSize);
			currentValue = hashArray[currentBucket][currentPosition];
		}
	}
	return false;
}

template<class ValueType>
inline size_t hashFunctionLevel1(const ValueType& value, size_t hashTableSize)
{
	assert(hashTableSize != 0);
	return ((3079 * value + 6291469) % BIG_PRIME_NUMBER) % hashTableSize;
}

int main()
{
	std::vector<int> setArray;
	InputNumbers(setArray);
	std::vector<int> requestsArray;
	InputNumbers(requestsArray);
	FixedSet<int> fixedSet(setArray);
	std::vector<bool> requestResults(requestsArray.size());
	ProcessRequests(fixedSet, requestsArray, requestResults);
	OutputResults(requestResults);
	return 0;
}

inline void InputNumbers(std::vector<int>& numbersArray)
{
	size_t numbersCount;
	std::cin >> numbersCount;
	assert(numbersCount > 0);
	numbersArray.resize(numbersCount);
	for (std::vector<int>::iterator currentNumber = numbersArray.begin(); currentNumber != numbersArray.end(); ++currentNumber)
	{
		std::cin >> *currentNumber;
	}
}

inline void ProcessRequests(const FixedSet<int>& fixedSet, const std::vector<int>& requestsArray, std::vector<bool>& requestResults)
{
	assert(requestsArray.size() == requestResults.size());
	for (size_t currentRequest = 0; currentRequest < requestsArray.size(); ++currentRequest)
	{
		requestResults[currentRequest] = fixedSet.Contains(requestsArray[currentRequest]);
	}
}

inline void OutputResults(const std::vector<bool>& requestResults)
{
	for (std::vector<bool>::const_iterator currentRequest = requestResults.begin(); currentRequest != requestResults.end(); ++currentRequest)
	{
		std::cout << ((*currentRequest) ? "Yes" : "No") << std::endl;
	}
}