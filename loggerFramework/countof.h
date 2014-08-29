
#ifndef __MCF_CRT_COUNTOF_HPP__
#define __MCF_CRT_COUNTOF_HPP__

#include <cstddef>

namespace __MCF {
	template<typename T, std::size_t N>
	char(*countof_helper(T(&)[N]))[N];

	template<typename T, std::size_t N>
	char(*countof_helper(T(&&)[N]))[N];
}

#define COUNTOF(ar) (sizeof(*::__MCF::countof_helper((ar))))

#endif