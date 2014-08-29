
#ifndef INCLUDE_OPTIONS_H
#define INCLUDE_OPTIONS_H

#include <string>
#include <vector>


class	options
{
public:

	void	add_option(const std::wstring& defined_option);
	void	add_options(const std::vector< std::wstring >& defined_options);

	bool	add_value(const std::wstring& name, const std::wstring& value);

	bool	is_supplied(const std::wstring& name)	const;
	std::wstring	first_value(const std::wstring& name)	const;
	bool	values(const std::wstring& name, std::vector< std::wstring >& values)	const;

private:

	struct option
	{
		std::wstring	name;
		std::vector< std::wstring >	values;
	};

	bool	is_defined_option(const std::wstring& name)	const;
	const option*	find(const std::wstring& name)	const;
	option*	find(const std::wstring& name);

private:

	typedef	std::vector< std::wstring >	defined_option_list;
	typedef	std::vector< option >	option_list;

	defined_option_list	defined_options_;
	option_list	options_;

};


bool	build_options(const std::wstring& cmd, options& opt);
bool	build_options(int argc, wchar_t* const argv[], options& opt);


/*
options opt;

opt.add_option(std::wstring(L"-a"));
opt.add_option(std::wstring(L"-b"));
opt.add_option(std::wstring(L"-c"));
opt.add_option(std::wstring(L"-d"));
opt.add_option(std::wstring(L"-e"));

if (build_options(std::wstring(L" -a=aOption -a=aOptionSecond -d -e -b=bOption "), opt) == false)
{
wprintf(L"error.\n");
return 0;
}

std::vector< std::wstring > m;
opt.values(std::wstring(L"-a"), m);
assert(m[0] == std::wstring(L"aOption"));
assert(m[1] == std::wstring(L"aOptionSecond"));

assert(opt.first_value(std::wstring(L"-b")) == std::wstring(L"bOption"));

assert(opt.is_supplied(L"-a"));
assert(opt.is_supplied(L"-d"));
assert(!opt.is_supplied(L"-k"));
assert(!opt.is_supplied(L"-f"));
*/

#endif