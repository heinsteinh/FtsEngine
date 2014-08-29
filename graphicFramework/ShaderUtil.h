
#ifndef ZEPHYR_GFX_UTIL
#define ZEPHYR_GFX_UTIL

#include "LibHeader.h"


namespace rosewood {
	namespace utils {

		struct UniformInfo {
			std::string type_name;
			size_t byte_size;
			GLenum element_type;
		};

		static void dump_current_shader_info();
		static void dump_shader_info(GLint program);
		static UniformInfo uniform_type_info(GLenum e);		

	}
}


#endif;