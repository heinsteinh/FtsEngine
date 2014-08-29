// commonFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ObjFunctor.h"

class Person
{
public:
	Person()
	{}

	~Person()
	{}
	

	int printName()
	{
		std::string nameToPrint = "Test";
		printf("name %s", nameToPrint);

		return 0;
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	Person* person= new Person;
	Omnibot::FunctorPtr f(new Omnibot::ObjFunctor<Person>(person, &Person::printName));

	
	return 0;
}

