#include "stdafx.h"
#include "Options.h"



void	options::add_option(const std::wstring& defined_option)
{
	if (!is_defined_option(defined_option))
	{
		defined_options_.push_back(defined_option);
	}
}

void	options::add_options(const std::vector< std::wstring >& defined_options)
{
	std::vector< std::wstring >::const_iterator pos = defined_options.begin();
	std::vector< std::wstring >::const_iterator end = defined_options.end();

	for (; pos != end; ++pos)
	{
		add_option(*pos);
	}
}

bool	options::add_value(const std::wstring& name, const std::wstring& value)
{
	if (is_defined_option(name))
	{
		option* opt = find(name);
		if (!opt)
		{
			option tmp;
			tmp.name = name;
			options_.push_back(tmp);

			opt = find(name);
		}

		if (!opt)
		{
			return false;
		}

		if (!value.empty())
		{
			opt->values.push_back(value);
		}

		return true;
	}

	return false;
}

bool	options::is_supplied(const std::wstring& name)	const
{
	if (find(name))
	{
		return true;
	}

	return false;
}

std::wstring	options::first_value(const std::wstring& name)	const
{
	const option* opt = find(name);
	if (opt)
	{
		if (!opt->values.empty())
		{
			return opt->values.front();
		}
	}

	return L"";
}

bool	options::values(const std::wstring& name, std::vector< std::wstring >& values)	const
{
	const option* opt = find(name);
	if (opt)
	{
		values = opt->values;
		return true;
	}

	return false;
}

bool	options::is_defined_option(const std::wstring& name)	const
{
	defined_option_list::const_iterator pos = defined_options_.begin();
	defined_option_list::const_iterator end = defined_options_.end();

	for (; pos != end; ++pos)
	{
		if (name == *pos)
		{
			return true;
		}
	}

	return false;
}

const options::option*	options::find(const std::wstring& name)	const
{
	const option* opt = 0;

	option_list::const_iterator pos = options_.begin();
	option_list::const_iterator end = options_.end();
	for (; pos != end; ++pos)
	{
		const option& tmp = (*pos);
		if (tmp.name == name)
		{
			opt = &tmp;
			break;
		}
	}

	return opt;
}

options::option*	options::find(const std::wstring& name)
{
	option* opt = 0;

	option_list::iterator pos = options_.begin();
	option_list::iterator end = options_.end();
	for (; pos != end; ++pos)
	{
		option& tmp = (*pos);
		if (tmp.name == name)
		{
			opt = &tmp;
			break;
		}
	}

	return opt;
}


#include "string_helper.h"

bool	build_options(std::vector< std::wstring >& arguments, options& opt)
{
	std::vector< std::wstring >::const_iterator pos = arguments.begin();
	std::vector< std::wstring >::const_iterator end = arguments.end();

	for (; pos != end; ++pos)
	{
		const std::wstring& arg = *pos;

		std::vector< std::wstring > options;
		crt::split(arg, options, L"=");

		std::wstring name;
		std::wstring value;
		if (options.size() >= 2)
		{
			name = options[0];
			value = options[1];
		}
		else
		{
			name = arg;
		}

		if (!name.empty())
		{
			if (opt.add_value(crt::trim(name), crt::trim(value)) == false)
			{
				return false;
			}
		}
	}

	return true;
}


bool	build_options(const std::wstring& cmd, options& opt)
{
	std::vector< std::wstring > arguments;
	crt::split(cmd, arguments, L" ");
	return build_options(arguments, opt);
}

bool	build_options(int argc, wchar_t* const argv[], options& opt)
{
	std::vector< std::wstring > arguments;
	for (int i = 1; i < argc; ++i)
	{
		arguments.push_back(std::wstring(argv[i]));
	}

	return build_options(arguments, opt);
}