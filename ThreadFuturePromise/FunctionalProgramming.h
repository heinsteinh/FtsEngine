#pragma once



#include <functional>
#include <string>

bool nonMemberFunction(int arg);

class  ResourceManager {
public:

};

class  SomeClass {
public:
	std::string memberFunction(double arg);
};

class  MapLoader {
public:
	bool loadResources(const ResourceManager& mgr, const std::string& path);
};