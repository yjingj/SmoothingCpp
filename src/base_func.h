#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define OUT 0
#define IN  1

using namespace std;

int countWords(char *str);




int countWords(char *str)
{
	int state = OUT;
	int wc = 0;  // word count

				 // Scan all characters one by one
	while (*str)
	{
		// If next character is a separator, set the 
		// state as OUT
		if (*str == ' ' || *str == '\t')
			state = OUT;

		// If next character is not a word separator and 
		// state is OUT, then set the state as IN and 
		// increment word count
		else if (state == OUT)
		{
			state = IN;
			++wc;
		}

		// Move to next character
		++str;
	}

	return wc;
};
