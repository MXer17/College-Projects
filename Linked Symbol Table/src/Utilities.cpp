/***************************************************************
<Nick Hancher>
<Utilities.cpp>
<CS210 Project 2>
<Calles the utilites in the header file>
***************************************************************/
#include <iostream>
#include <algorithm>
#include <map>
#include <random>
#include <string>

#include "Utilities.h"

std::default_random_engine         Utilities::_generator{ 0 };
std::uniform_int_distribution<int> Utilities::_distribution{ 0, 100000 }; // Consistent seed, in range [0, 100000];