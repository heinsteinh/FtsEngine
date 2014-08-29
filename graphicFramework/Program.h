/**
* @file Program.hpp
*/

#ifndef ZEPHYR_GFX_PROGRAM_HPP_
#define ZEPHYR_GFX_PROGRAM_HPP_

//#include <zephyr/gfx/Shader.hpp>
//#include <GL/glew.h>
//#include <GL/gl.h>


#include "Shader.h"
#include "ShaderParameter.h"
#include "ShaderAttribute.h"


#include <memory>
#include <vector>
#include <unordered_map>


namespace zephyr {
	namespace gfx {

		namespace detail {

		
			

			inline void Validate(const int & s){
				int res;
				glValidateProgram(s);
				glGetProgramiv(s, GL_VALIDATE_STATUS, &res);
				printf("validation of program %d:%d \n", s, res);
								


				glGetProgramiv(s, GL_LINK_STATUS, &res);
				printf("linking of program %d:%d \n", s, res);

				glGetProgramiv(s, GL_ACTIVE_ATTRIBUTES, &res);
				printf("active attribute of program %d:%d \n", s, res);

				glGetProgramiv(s, GL_ACTIVE_UNIFORMS, &res);
				printf("active uniform of program %d:%d \n", s, res);

				glGetProgramiv(s, GL_ACTIVE_UNIFORM_MAX_LENGTH, &res);
				printf("active uniform Max Length of program %d:%d \n", s, res);
			}

			inline void checkCreationStatus(GLuint program) {
				int status;
				glGetProgramiv(program, GL_LINK_STATUS, &status);
				if (status != GL_TRUE) {
					GLint infoLength;
					glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
					std::vector<GLchar> buffer(infoLength + 1);
					glGetProgramInfoLog(program, infoLength, nullptr, buffer.data());

					throw std::runtime_error(util::format(
						"Error while linking program: {}", buffer.data()));
				}

				
				
				glValidateProgram(program);
				glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
				if (status != GL_TRUE) {
					GLint infoLength;
					glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
					std::vector<GLchar> buffer(infoLength + 1);
					glGetProgramInfoLog(program, infoLength, nullptr, buffer.data());

					throw std::runtime_error(util::format(
						"Error while validate program: {}", buffer.data()));
				}

				//Validate(program);			

				GL_CHECK
			}

			template <typename Iter>
			GLuint create(Iter begin, Iter end) {
				GLuint program = glCreateProgram();
				for (Iter s = begin; s != end; ++s) {
					glAttachShader(program, (*s)->ref());
				}
				glLinkProgram(program);


				checkCreationStatus(program);
				/*for (Iter s = begin; s != end; ++s) {
					glDetachShader(program, (*s)->ref());
				}*/

				//Validate(program);
				GL_CHECK
				return program;
			}


			

			inline const std::unordered_map<std::string, Terrene::ShaderParameterPtr> getUniforms(GLuint program)
			{
				std::unordered_map<std::string, Terrene::ShaderParameterPtr> uniforms;

				GLint	n = -1, maxLen = -1;
				GLint	size = -1, location = - 1;
				GLsizei	written;
				GLenum	type;
				GLchar*	name;

				(glLinkProgram(program));
				checkCreationStatus(program);

				glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
				GL_CHECK
				glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &n);
				GL_CHECK
				name = new GLchar[maxLen];
				for (int i = 0; i < n; ++i)
				{
					glGetActiveUniform(program, i, maxLen, &written, &size, &type, name);
					location = glGetUniformLocation(program, name);
					Terrene::ShaderParameterPtr param = Terrene::ShaderParameterPtr(new Terrene::ShaderParameterImpl(name, type, location));
					uniforms[name] = param;
				}
				delete[] name;


				return uniforms;
			}

			inline std::unordered_map<std::string, Terrene::ShaderParameterPtr> getUniformBlocks(GLuint program)
			{				
				std::unordered_map<std::string, Terrene::ShaderParameterPtr> uniforms;
				
				GLint	n = -1, maxLen = -1;
				GLint	size = -1, location = -1;
				GLsizei	written;
				GLenum	type;
				GLchar*	name;

				(glLinkProgram(program));
				glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
				glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &n);
				name = new GLchar[maxLen];
				for (int i = 0; i < n; ++i)
				{
					glGetActiveUniform(program, i, maxLen, &written, &size, &type, name);
					location = glGetUniformLocation(program, name);
					Terrene::ShaderParameterPtr param(new Terrene::ShaderParameterImpl(name, type, location));
					uniforms[name] = param;
				}
				delete[] name;				
			

				return uniforms;
			}

			inline std::unordered_map<std::string, Terrene::ShaderAttributePtr> getAttributes(GLuint program)
			{
				std::unordered_map<std::string, Terrene::ShaderAttributePtr> attributes;


				GLint	n, maxLen;
				GLint	size, location;
				GLsizei	written;
				GLenum	type;
				GLchar*	name;

				(glLinkProgram(program));
				glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLen);
				glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &n);
				name = new GLchar[maxLen];
				for (int i = 0; i < n; ++i)
				{
					glGetActiveAttrib(program, i, maxLen, &written, &size, &type, name);
					location = glGetAttribLocation(program, name);

					Terrene::ShaderAttributePtr param(new Terrene::ShaderAttribute(name, type, location, size));
					attributes[name] = param;
				}
				/**********************************************************************/
				delete[] name;

				return attributes;
			}



			template <typename Iter>
			GLuint create_and_get(Iter begin, Iter end,
				std::unordered_map<std::string, Terrene::ShaderParameterPtr>& unif,
				std::unordered_map<std::string, Terrene::ShaderAttributePtr >& attri) {
				GLuint program = glCreateProgram();
				for (Iter s = begin; s != end; ++s) {
					glAttachShader(program, (*s)->ref());
				}
				
				attri = getAttributes(program);

				glLinkProgram(program);

				checkCreationStatus(program);

				unif = getUniforms(program);
				


				for (Iter s = begin; s != end; ++s) {
					glDetachShader(program, (*s)->ref());
				}

				GL_CHECK
					return program;
			}
			

		} /* namespace detail */


		class Program : public std::enable_shared_from_this<Program>
		{
		public:
			typedef std::unordered_map<std::string, Terrene::ShaderParameterPtr> UniformMap;
			typedef std::unordered_map<std::string, Terrene::ShaderParameterPtr> UniformBlockMap;			
			typedef std::unordered_map<std::string, Terrene::ShaderAttributePtr> AttributeMap;


			template <typename Iter>
			Program(Iter begin, Iter end)
				: program_{ detail::create(begin, end ) }
				, uniforms_{ detail::getUniforms(program_) }
				, attribute_{ detail::getAttributes(program_) }
				//, uniformBlocks_{ detail::getUniformBlocks(program_) }
			{ }

			template <typename Container>
			Program(const Container& shaders)
				: Program(begin(shaders), end(shaders))
			{ }

			Program(std::initializer_list<ShaderPtr> shaders)
				: Program(begin(shaders), end(shaders))
			{ }

			~Program() {
				glDeleteProgram(program_);				
			}

			GLuint ref() const {
				return program_;
			}

			GLint uniformLocation(const char* name) const {
				GLint location = glGetUniformLocation(program_, name);
				if (location != -1) {
					return location;
				}
				else {
					return -1;
					// throw std::runtime_error(util::format(
					// "Cannot get location of \"{}\" uniform variable", name));
				}
			}

			GLint uniformLocation(const std::string& name) const {
				auto it = uniforms_.find(name);
				if (it != uniforms_.end()) {
					return it->second->location;
				}
				else {
					return -1;
					// throw std::runtime_error(util::format(
					// "Cannot get location of \"{}\" uniform variable", name));
				}
			}

			GLint uniformBlockIndex(const char* name) const {
				return uniformBlockIndex(std::string{ name });
			}

			Terrene::ShaderAttributePtr getAttribute(const std::string& name)
			{
				auto it = attribute_.find(name);
				if (it != attribute_.end()) {
					return it->second;
				}
				else {
					return nullptr;
				}
			}
			Terrene::ShaderParameterPtr getUniform(const std::string& name)
			{
				auto it = uniforms_.find(name);
				if (it != uniforms_.end()) {
					return it->second;
				}
				else {
					return nullptr;
				}
			}

			GLint uniformBlockIndex(const std::string& name) const {
				auto it = uniforms_.find(name);
				if (it != uniforms_.end()) {
					return it->second->location;
				}
				else {
					return -1;
					/* throw std::runtime_error(util::format(
					 "Cannot get location of \"{}\" uniform block", name));*/
				}
			}

			const UniformMap& uniforms() const {
				return uniforms_;
			}

			const AttributeMap& attributeLoc() const {
				return attribute_;
			}

			void printDebug()
			{
				/*std::cout << "Attributes:" << std::endl;
				for (std::map<std::string, Terrene::ShaderAttributePtr>::iterator it = attribute_.begin(); it != attribute_.end(); ++it)
					std::cout << "Name: " << (*it).first << std::endl;
				std::cout << "Uniforms:" << std::endl;
				for (std::map<std::string, Terrene::ShaderParameterPtr>::iterator it = uniforms_.begin(); it != uniforms_.end(); ++it)
					std::cout << "Name: " << (*it).first << std::endl;*/
			}

		private:

			GLuint				program_;

			UniformMap			uniforms_;
			AttributeMap		attribute_;
			UniformBlockMap		uniformBlocks_;
			
		};


		inline bool operator == (const Program& a, const Program& b) {
			return a.ref() == b.ref();
		}

		inline bool operator != (const Program& a, const Program& b) {
			return !(a == b);
		}

		typedef std::shared_ptr<Program> ProgramPtr;

		template <typename... Args>
		inline ProgramPtr newProgram(Args&&... args) {
			return std::make_shared<Program>(std::forward<Args>(args)...);
		}

		inline ProgramPtr newProgram(std::initializer_list<ShaderPtr> shaders) {
			return std::make_shared<Program>(shaders);
		}


	} /* namespace gfx */
} /* namespace zephyr */

#endif /* ZEPHYR_GFX_PROGRAM_HPP_ */