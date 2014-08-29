#include "stdafx.h"
#include "console_command_parser.h"


#include <assert.h>
#include <cstdint>

using namespace std;

namespace wmdf
{
	ConsoleCommandParser::ConsoleCommandParser(void)
	{
	}

	ConsoleCommandParser::~ConsoleCommandParser(void)
	{
	}

	std::string ConsoleCommandParser::ParseCommandName(const std::string& command_line)
	{

		vector<std::string> params = SpliteCommand<string>(std::string(command_line), std::string(" "));
		if (params.size() <= 0)
		{
			assert(params.size() >= 1);
			return " ";
		}
		return params[0];
	}

	std::vector<std::string> ConsoleCommandParser::ParseCommandParameters(const std::string& command_line)
	{
		std::vector<std::string> params = SpliteCommand<string>(string(command_line), std::string(" "));
		assert(params.size() >= 1);
		vector<string> parameters;
		for (uint32_t index = 0; index < params.size(); index++)
		{
			parameters.push_back(params[index]);
		}

		return parameters;
	}
}