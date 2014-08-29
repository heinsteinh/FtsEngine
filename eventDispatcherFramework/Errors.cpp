#include "stdafx.h"


#include "errors.h"

namespace module
{
	//////////////////////////////////////////////////////////////////////////

	const std::error_category& module_category()
	{
		static module_category_impl cat;
		return cat;
	}

	//////////////////////////////////////////////////////////////////////////

	const char* module_category_impl::name() const
	{
		return "module";
	}

	//////////////////////////////////////////////////////////////////////////

	std::string module_category_impl::message(module_error errval) const
	{
		switch (errval)
		{
		case module_error::no_interface:
			return "No interface";
		case module_error::invalid_pointer:
			return "Invalid pointer";
		default:
			return "<unknown module error>";
		}
	}

	//////////////////////////////////////////////////////////////////////////

	std::error_condition module_category_impl::default_error_condition(module_error errval) const
	{
		switch (errval)
		{
		case module_error::invalid_pointer:
			return std::errc::invalid_argument;
		case module_error::no_interface:
			return std::errc::not_supported;
		default:
			return std::error_condition(errval, *this);
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace



