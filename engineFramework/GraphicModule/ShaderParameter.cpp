#include "stdafx.h"
#include "ShaderParameter.h"

#include "LibHeader.h"

namespace Terrene
{
	//--------------------------------------------------------------------------------------

	//class ShaderParameterImpl : public IShaderParameter
	//{
	//public:
	//	const std::string& GetName() const { return name; }

	//	ShaderParameterImpl(const std::string& name, GLenum type, GLuint location)
	//		: name(name), type(type), location(location), dirty(false)
	//	{
	//		(void)memset(cache, 0, sizeof(cache));
	//	}

	//	virtual ~ShaderParameterImpl()
	//	{
	//	}

	//	virtual void Set(float value) { CacheValue(&value, sizeof(value)); }
	//	virtual void Set(const glm::vec2& value) { CacheValue(&value, sizeof(value)); }
	//	virtual void Set(const glm::vec3& value) { CacheValue(&value, sizeof(value)); }
	//	virtual void Set(const glm::vec4& value) { CacheValue(&value, sizeof(value)); }
	//	virtual void Set(const glm::mat2& value) { CacheValue(&value, sizeof(value)); }
	//	virtual void Set(const glm::mat3& value) { CacheValue(&value, sizeof(value)); }
	//	virtual void Set(const glm::mat4& value) { CacheValue(&value, sizeof(value)); }

	//	virtual float GetFloat() { float value; GetValue(&value, sizeof(value)); return value; }
	//	virtual glm::vec2 GetVec2() { glm::vec2 value; GetValue(&value, sizeof(value)); return value; }
	//	virtual glm::vec3 GetVec3() { glm::vec3 value; GetValue(&value, sizeof(value)); return value; }
	//	virtual glm::vec4 GetVec4() { glm::vec4 value; GetValue(&value, sizeof(value)); return value; }
	//	virtual glm::mat2 GetMat2() { glm::mat2 value; GetValue(&value, sizeof(value)); return value; }
	//	virtual glm::mat3 GetMat3() { glm::mat3 value; GetValue(&value, sizeof(value)); return value; }
	//	virtual glm::mat4 GetMat4() { glm::mat4 value; GetValue(&value, sizeof(value)); return value; }

	//	virtual void Update()
	//	{
	//		if (dirty)
	//		{
	//			dirty = false;
	//			switch (type)
	//			{
	//			case GL_FLOAT: glUniform1fv(location, 1, (float*)cache); break;
	//			case GL_FLOAT_VEC2: glUniform2fv(location, 1, (float*)cache); break;
	//			case GL_FLOAT_VEC3: glUniform3fv(location, 1, (float*)cache); break;
	//			case GL_FLOAT_VEC4: glUniform4fv(location, 1, (float*)cache); break;
	//			case GL_FLOAT_MAT3: glUniformMatrix3fv(location, 1, GL_FALSE, (float*)cache); break;
	//			case GL_FLOAT_MAT4: glUniformMatrix4fv(location, 1, GL_FALSE, (float*)cache); break;
	//			default: assert(false);  break; // ASSERTM(false, "unsupported type used in shader"); break;
	//			}
	//		}
	//	}

	//private:
	//	void CacheValue(const void* value, size_t sizeInBytes)
	//	{
	//		if (0 != memcmp(value, cache, sizeInBytes))
	//		{
	//			dirty = true;
	//			memcpy(cache, value, sizeInBytes);
	//		}
	//	}

	//	void GetValue(void* value, size_t sizeInBytes) { memcpy(value, cache, sizeInBytes); }

	//	std::string name;
	//	const GLenum type;
	//	const GLuint location;
	//	bool dirty;
	//	unsigned char cache[sizeof(glm::mat4)];
	//};


}