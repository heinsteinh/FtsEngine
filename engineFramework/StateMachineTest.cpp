#include "stdafx.h"
#include "StateMachineTest.h"


namespace TestStateMachine
{
	////////////////////////////////////////

	cCppIdentifierRecognizer::cCppIdentifierRecognizer()
		: tStateMachine(&m_initialState)
		, m_charOkState(&cCppIdentifierRecognizer::OnEnterCharOk, &cCppIdentifierRecognizer::OnExitCharOk, &cCppIdentifierRecognizer::OnUpdateCharOk)
	{
	}

	////////////////////////////////////////

	cCppIdentifierRecognizer::~cCppIdentifierRecognizer()
	{
	}

	////////////////////////////////////////

	void cCppIdentifierRecognizer::Reset()
	{
		GotoState(&m_initialState);
		m_identifier.clear();
	}

	////////////////////////////////////////

	void cCppIdentifierRecognizer::AddChar(const char& c)
	{
		if (IsCurrentState(&m_initialState))
		{
			if ((c == ('_')) || _istalpha(c))
			{
				m_identifier.push_back(c);
				GotoState(&m_charOkState);
			}
			else
			{
				GotoState(&m_errorState);
			}
		}

		else if (IsCurrentState(&m_charOkState))
		{
			if ((c == _T('_')) || _istalpha(c) || _istdigit(c))
			{
				m_identifier.push_back(c);
			}
			else
			{
				GotoState(&m_errorState);
			}
		}
	}

	////////////////////////////////////////

	bool cCppIdentifierRecognizer::GetIdentifier(std::string* pIdent) const
	{
		if (IsCurrentState(&m_charOkState))
		{
			*pIdent = m_identifier[0]; //&m_identifier[0];
			return true;
		}
		return false;
	}

	////////////////////////////////////////

	bool cCppIdentifierRecognizer::OnEnterCharOk()
	{
		return true;
	}

	////////////////////////////////////////

	bool cCppIdentifierRecognizer::OnExitCharOk()
	{
		return true;
	}

	////////////////////////////////////////

	void cCppIdentifierRecognizer::OnUpdateCharOk(double)
	{

	}


	///////////////////////////////////////////////////////////////////////////////
}