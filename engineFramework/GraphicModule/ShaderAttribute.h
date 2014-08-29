#if ! defined(__SHADER_ATTRIBUTE_H__)
#define __SHADER_ATTRIBUTE_H__

#include <list>
#include "LibHeader.h"


namespace Terrene
{

	class ShaderAttribute
	{
	public:
		const std::string Name;
		const GLenum	Type;
		const int	Location;
		const size_t	ComponentCount;

		ShaderAttribute(const char* const name, GLenum type, int location, size_t componentCount):
			Name(name), Type(type), Location(location), ComponentCount(componentCount){}
	};

	typedef std::shared_ptr<ShaderAttribute> ShaderAttributePtr;
	typedef std::list<ShaderAttributePtr> ShaderAttributeCollection;
}

#endif // __SHADER_ATTRIBUTE_H__