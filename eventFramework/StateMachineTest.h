#pragma once

#include <string>
#include <vector>

#include "StateMachine.h"

namespace TestStateMachine
{
	//https://github.com/dpalma/sge/blob/98357c91eb77d6effe50dd11e926fb637f68a295/tech/statemachinetest.cpp

	class cCppIdentifierRecognizer : public core::cStateMachine<cCppIdentifierRecognizer, double>
	{
	public:
		cCppIdentifierRecognizer();
		~cCppIdentifierRecognizer();

		void Reset();

		void AddChar(const char& c);
		bool GetIdentifier(std::string* pIdent) const;

		bool OnEnterCharOk();
		bool OnExitCharOk();
		void OnUpdateCharOk(double);

	private:
		tState m_initialState;
		tState m_charOkState;
		tState m_errorState;
		std::vector<char>  m_identifier;
	};
}

/*

typedef const struct tests_
{
const char* pszIdent;
bool result;
}tests_type;

tests_type tests[6] =
{
	{ ("0000"), false },
	{ ("i"), true },
	{ ("_variable"), true },
	{ ("member1234"), true },
	{ ("this->foo"), false },
	{ ("foo.bar"), false },
};


TestStateMachine::cCppIdentifierRecognizer r;
for (int i = 0; i < _countof(tests); i++)
{
	r.Reset();
	int len = strlen(tests[i].pszIdent);

	for (int j = 0; j < len; j++)
	{
		r.AddChar(tests[i].pszIdent[j]);
	}

	std::string ident;
	bool result = r.GetIdentifier(&ident);
	if (result)
	{
		assert(ident.compare(tests[i].pszIdent) == 0);
	}
	assert(result == tests[i].result);
}
*/