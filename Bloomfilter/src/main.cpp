/***************************************************************
<Nick Hancher>
<main.cpp>
<CS210 Prj4>
<Testest he code that is acquired from BloomFilter.hpp. It loops from a fixed rate of
 1/4 to 1/2^10. Within this loop it will add elements to a BloomFilter from the sizes
 of 16 to 2^23. Whilst doing so it tests adding which the time complexity for it is O(h)
 and then tests for false positives using contains, which also has a time complexity of O(h). >
***************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h> 
#include <math.h>
#include "MurmurHash3.h"
#include "BloomFilter.hpp"


int main()
{
	
	const long LOWER_SIZE = 16;
	const long UPPER_SIZE = pow(2, 23);
	double rate = 0.25;

	//Loop to get the hashes from 1 to hashes 10;
	while (rate != 1 / pow(2,11))
	{
		//Loops from 2^4 to 2^23 to then add those elements to the Bloom Filter
		for (long size = LOWER_SIZE; size <= UPPER_SIZE; size *= 2) 
		{
			std::cout << "Bloom Filter characteristics:" << std::endl;
			std::cout << "Flase Positive Rate: " << std::fixed << rate << std::endl;
			//calculate bits you have to find the numerator and denom the put them together so
			//you dont divide 
			double num = -(size * log(rate));
			double denom = pow(log(2), 2);
			int bits = num / denom;
			//Calculatesthe hash num by doing bits divided by size, then multiplying by ln 2
			uint8_t hashNum = (bits / size) *log(2);
			//Creates a Bloom Filter
			BloomFilter filter(bits, hashNum);
			//Adds elements from 0 to the size of the number of elements
			for (long i = 0; i <size; i++)
			{

				filter.add((const uint8_t*)(&i), sizeof(int));
			}
			
			std::cout << "Elements (N): " << size << std::endl;
			std::cout << "Bits (b): " << bits << std::endl;
			std::cout << "Hash Functions (h): " << unsigned(hashNum)<<  std::endl;

			double numOfFP = 0;
			//Checks from size to 2 *size to see if it is contains in the BloomFilter
			//If it isnt contained, adds 1 to numOfFP, if not does nothing

			for (int i = size; i < size * 2; i++)
			{
				if (!filter.possiblyContains((const uint8_t*)(&i), sizeof(int)))
				{
					numOfFP++;

				}
			}
			
			//Calculates the rate of false positives in the Bloom Filter
			//by doing (1- e^- of false positives * hash num / bits) ^ hash num
			double falseP = pow(1 - exp(-numOfFP*hashNum / bits), hashNum);
			std::cout << "Rate of false positives: " << std::setprecision(10) << falseP << std::endl;
			std::cout << "   " << std::endl;
		}
		//updates to continue the while loop
		rate /= 2;
	}
	system("pause");

	return 0;
}