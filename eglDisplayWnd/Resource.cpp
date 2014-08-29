#include "stdafx.h"



#include <iostream>
#include <string>
#include <unordered_map>


#include "Resource.h"

namespace ANAS {

	typedef std::unordered_map< std::string, ResourceHolder* > ResourceMap;

	class ResourceImpl {

	public:
		ResourceMap MapData;

		ResourceImpl(){}
		~ResourceImpl(){


			for each (ResourceMap::value_type value in MapData){
				delete value.second;
			}

		}

	};
}

ANAS::Resource::Resource(){

	pImpl = new ResourceImpl;
}

ANAS::Resource::~Resource(){

	if (pImpl){
		delete pImpl;

		pImpl = NULL;
	}
}


void ANAS::Resource::Set(const std::string &Name, ResourceHolder* pHold){

	pImpl->MapData[Name] = pHold;
}


ANAS::ResourceHolder *ANAS::Resource::Get(const std::string &Name){


	if (pImpl->MapData.count(Name)){

		return pImpl->MapData.at(Name);

	}
	else {
		return NULL;
	}
}


void ANAS::Resource::Release(const std::string &Name){

	if (pImpl->MapData.count(Name)){

		pImpl->MapData.erase(Name);
	}
}