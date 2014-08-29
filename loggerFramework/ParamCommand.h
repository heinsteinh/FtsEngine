#pragma once

#include <string>
#include "MyType.h"

//https://github.com/kihx/rasterizer/blob/ac5361c9547619a4c97fb34c7d313847571808c3/coold/Console/CoolD_ConsoleManager.h

namespace core
{

	class Command
	{
	private:
		Command() = delete;
		Command(const Command&) = delete;
		Command& operator=(const Command&) = delete;
	protected:
		Command(const std::string& Name);

	public:
		virtual ~Command();

	public:
		inline std::string GetCommandName()	const	{ return m_Name; }

	public:
		virtual void Execute(std::initializer_list<std::string> strs) = 0;
		virtual void ShowCommand() = 0;

	protected:
		const std::string m_Name;
	};


	class VariableCommand : public Command
	{
	public:
		VariableCommand(const std::string& Name, const std::string& value);
		virtual ~VariableCommand();

	public:
		inline const std::string& String()	const { return m_Str; }
		inline const int Integer()	const { return m_Integer; }
		inline const float Float()	const { return m_Float; }
		inline const bool Bool()	const { return m_Float != 0; }

	public:
		void SetValue(const std::string& Str);
		void SetValue(int Integer);
		void SetValue(float Float);

	public:
		virtual void Execute(std::initializer_list<std::string> strs);
		virtual void ShowCommand();

	private:
		std::string	m_Str;
		int	m_Integer;
		float	m_Float;
	};


	class FunctionCommand : public Command
	{
	public:
		FunctionCommand(const std::string& Name, Func_void_initList func = nullptr);
		virtual ~FunctionCommand();
	public:
		virtual void Execute(std::initializer_list<std::string> strs);
		virtual void ShowCommand();

	private:
		Func_void_initList m_Func;
	};
};