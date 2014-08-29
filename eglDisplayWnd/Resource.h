#pragma once
#ifndef __DEFINED_ANAS_RESOURCE__
#define __DEFINED_ANAS_RESOURCE__

#include <string>
#include "TSingleton.h"

namespace ANAS {


	
	class ResourceHolder {
	public:
		virtual ~ResourceHolder(){}

	};



	template< class T >
	class ResourceItem : public ResourceHolder {
	private:
		T *holder;
	public:

		ResourceItem(T *item)
			: holder(item)
		{

		}

		~ResourceItem(){
			delete holder;
		}

		T *Get(){
			return holder;
		}

	};

	
	class ResourceImpl;


	class Resource :public  core::CSingleton<Resource>
	{
		friend class core::CSingleton<Resource>;

	private:
		ResourceImpl *pImpl;

	public:

		Resource();
		~Resource();

		
		void Set(const std::string &, ResourceHolder*);

		
		ResourceHolder* Get(const std::string &);

		
		void Release(const std::string &);
	};
}


#endif /* __DEFINED_ANAS_RESOURCE__ */