#include "stdafx.h"
#include "Named.h"


namespace util {
	Named::Named(const std::string& name) {
		setName(name);
	}

	Named::~Named() {
	}

	void Named::setName(const std::string& name) {
		mName = name;
	}

	const std::string& Named::getName() const {
		return mName;
	}
}
