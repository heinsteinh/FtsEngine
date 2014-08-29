#ifndef _MODULE_ERRORS_H__
#define _MODULE_ERRORS_H__

#include "module_fwd.h"
#include <system_error>

namespace module
{

	//////////////////////////////////////////////////////////////////////////

	/// \todo refactor to 'enum class' when will be available
#ifdef COMPILER_MSC
# pragma warning(disable : 4482)
#endif

	/// Error codes
	/** @ingroup module */
	enum module_error
	{
		no_interface = 1,
		invalid_pointer = 2,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Error category for module error codes
	/** @ingroup module */
	class module_category_impl : public std::error_category
	{
	public:
		virtual const char* name() const;
	
		
		virtual std::string message(module_error errval) const;
		virtual std::error_condition default_error_condition(module_error errval) const;
	};

	MODULE_API const std::error_category& module_category();

	//////////////////////////////////////////////////////////////////////////

	inline std::error_code make_error_code(module_error errc)
	{
		return std::error_code(static_cast<int>(errc), module_category());
	}

	//////////////////////////////////////////////////////////////////////////

	inline std::error_condition make_error_condition(module_error errc)
	{
		return std::error_condition(static_cast<int>(errc), module_category());
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace

//////////////////////////////////////////////////////////////////////////

namespace std
{
	template <>
	struct is_error_code_enum<module::module_error> : public true_type
	{};
}

//////////////////////////////////////////////////////////////////////////

#endif //_MODULE_ERRORS_H__