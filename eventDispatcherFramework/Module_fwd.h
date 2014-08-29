#ifndef _MODULE_FWD_H__
#define _MODULE_FWD_H__

#include "platform.h"

#if defined BUILD_SHARED && defined MODULE_EXPORTS
# define MODULE_API SHARED_EXPORT
#else
# define MODULE_API SHARED_IMPORT
#endif

namespace module
{
	struct guid;
	struct IUnknown;
	struct IClassFactory;
	class Exception;
}

#endif //_MODULE_FWD_H__