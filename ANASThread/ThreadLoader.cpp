#include "stdafx.h"
#include "ThreadLoader.h"


namespace ANAS
{

	ThreadLoader::ThreadLoader()
	{
	}


	ThreadLoader::~ThreadLoader()
	{
	}

	/*
	static string textFileRead(const char *fileName)
	{
		string fileString = string(); // A string for storing the file contents
		string line = string(); // A string for holding the current line

		ifstream file(fileName); // Open an input stream with the selected file
		if (file.is_open()) // If the file opened successfully
		{
			while (!file.eof()) // While we are not at the end of the file
			{
				getline(file, line); // Get the current line
				fileString.append(line); // Append the line to our file string
				fileString.append("\n"); // Append a new line character
			}
			file.close(); // Close the file
		}

		return fileString; // Return our string
	}*/

}
