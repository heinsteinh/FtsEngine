#ifndef _OBJECT_FACTORY_H_

#include <map>
using namespace std;

//-------------------------------------------------------------------------------------------
// ObjectFactory :
// Template class used to create object factories.
//-------------------------------------------------------------------------------------------
template <typename Object, typename ObjectIdentifier, typename Creator = Object* (*)()>
class ObjectFactory
{
public:
	virtual ~ObjectFactory(void)
	{
		creatorsMap.clear();
	}

	/**
	* Subscribe an object creator to the factory.
	*/
	bool Subscribe(const ObjectIdentifier& /*id*/, Creator /*creator*/);

	/**
	* Unsubscribe an object creator to the factory.
	*/
	bool Unsubscribe(const ObjectIdentifier& /*id*/);

	/**
	* Create an already subscribed object.
	*/
	Object* Create(const ObjectIdentifier& /*id*/);

private:
	/**
	* Map containing each creator associated to its identifier type.
	*/
	map<ObjectIdentifier, Creator> creatorsMap;
};

template <typename Object, typename ObjectIdentifier, typename Creator>
bool ObjectFactory<Object, ObjectIdentifier, Creator>::Subscribe(const ObjectIdentifier& id, Creator creator) {
	creatorsMap[id] = creator;
}

template <typename Object, typename ObjectIdentifier, typename Creator>
bool ObjectFactory<Object, ObjectIdentifier, Creator>::Unsubscribe(const ObjectIdentifier& id) {
	return creatorsMap.erase(id) == 1;
}

template <typename Object, typename ObjectIdentifier, typename Creator>
Object* ObjectFactory<Object, ObjectIdentifier, Creator>::Create(const ObjectIdentifier& id) {
	map<ObjectIdentifier, Creator>::const_iterator it = creatorsMap.find(id);
	if (it != creatorsMap.end()) {
		return (it->second)();
	}
	return NULL;
}

#endif // _OBJECT_FACTORY_H_