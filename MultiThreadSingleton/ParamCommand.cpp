#include "stdafx.h"
#include "MyType.h"
#include "ParamCommand.h"
#include "MyDefines.h"
#include "ConsoleManager.h"

namespace core
{

	using namespace std;
	//---------------------------------------------------------------
	Command::Command(const string& Name):m_Name(Name)
	{
		GETSINGLE(ConsoleManager).AddCommand(this);
	}

	Command::~Command()
	{

	}

	//---------------------------------------------------------------
	VariableCommand::VariableCommand(const string& Name, const string& value)
		: Command(Name)
	{
		SetValue(value);
	}

	VariableCommand::~VariableCommand()
	{
	}

	void VariableCommand::SetValue(const string& Str)
	{
		m_Str = Str;
		m_Integer = stoi(Str);
		m_Float = stof(Str);
	}

	void VariableCommand::SetValue(int Integer)
	{
		m_Str = to_string(Integer);
		m_Integer = Integer;
		m_Float = (float)Integer;
	}

	void VariableCommand::SetValue(float Float)
	{
		m_Str = to_string(Float);
		m_Integer = (int)Float;
		m_Float = Float;
	}

	void VariableCommand::Execute(initializer_list<string> strs)
	{
		if (strs.size() >= 1)
		{
			for (auto paramIter = begin(strs); paramIter != end(strs); ++paramIter)
			{
				if (paramIter == begin(strs))
				{
					SetValue(*paramIter);	
				}
				else
				{
					cout << (*paramIter) + " is abandoned" << endl;
				}
			}
		}
		else
		{
			LOG("InitializerList Size < 1");
		}
	}

	void VariableCommand::ShowCommand()
	{
		cout << "\nVariable---------------------------------" << endl;
		cout << "Name : " << m_Name << endl;
		cout << "Value : " << m_Str << endl;
		cout << "-----------------------------------------" << endl;
	}

	//---------------------------------------------------------------
	FunctionCommand::FunctionCommand(const string& Name, Func_void_initList func /*= nullptr */)
		: Command(Name)
	{
		m_Func = func;
	}

	FunctionCommand::~FunctionCommand()
	{
	}

	void FunctionCommand::Execute(initializer_list<string> strs)
	{
		if (m_Func != nullptr)
		{
			m_Func(strs);
		}
	}

	void FunctionCommand::ShowCommand()
	{
		cout << "\nFunction---------------------------------" << endl;
		cout << "Name : " << m_Name << endl;
		cout << "-----------------------------------------" << endl;
	}
};