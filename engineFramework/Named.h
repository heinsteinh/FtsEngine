#pragma once

#include "Lib.h"

namespace util 
{
	class  Named {
	public:
		Named(const std::string& name);
		virtual ~Named();

		const std::string& getName() const;

	protected:
		void setName(const std::string& name);

	private:
		std::string mName;
	};
}
