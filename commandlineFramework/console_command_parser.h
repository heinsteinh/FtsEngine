#pragma once



#include <string>
#include <vector>

namespace wmdf
{

	class ConsoleCommandParser
	{
	public:
		ConsoleCommandParser(void);
		~ConsoleCommandParser(void);

	public:
		static std::string ParseCommandName(const std::string& command_line);
		static std::vector<std::string> ParseCommandParameters(const std::string& command_line);

	private:
		template<typename T>
		static  std::vector<T> SpliteCommand(const T& str, const T& delimiters);
	};


	template<class T>
	std::vector<T> ConsoleCommandParser::SpliteCommand(const T& str, const T& delimiters)
	{
		std::vector<T> v;
		T::size_type start = 0;
		auto pos = str.find_first_of(delimiters, start);
		while (pos != T::npos)
		{
			if (pos != start) // ignore empty tokens
			{
				v.emplace_back(str, start, pos - start);
			}
			start = pos + 1;
			pos = str.find_first_of(delimiters, start);
		}

		if (start < str.length()) // ignore trailing delimiter
		{
			v.emplace_back(str, start, str.length() - start); // add what's left of the string
		}
		return v;
	}
}

