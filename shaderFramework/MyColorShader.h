

#pragma once 

#include "MyShader.h"

namespace octet {
	class color_shader : public Shader {
		// indices to use with glUniform*()

		// index for model space to projection space matrix
		GLuint modelToProjectionIndex_;

		// index for flat shader emissive color
		GLuint emissive_colorIndex_;


	public:

		void init() {
			// this is the vertex shader. main() will be called for every vertex
			// of every triangle. The output is gl_Position which is used to generate
			// 2D triangles in the rasterizer.
			const char vertex_shader[] = SHADER_STR(
				attribute vec4 pos;
			uniform mat4 modelToProjection;
			void main() { gl_Position = modelToProjection * pos; }
			);

			// this is the fragment shader. It is called once for every pixel
			// in the rasterized triangles.
			const char fragment_shader[] = SHADER_STR(
				uniform vec4 emissive_color;
			void main() { gl_FragColor = emissive_color; }
			);

			
			Load(vertex_shader, fragment_shader);
		}

		void BindAttibuteLoc()
		{

			glBindAttribLocation(GetProgram(), 0, "pos");

			//// set up handles to access the uniforms.
			//modelToProjectionIndex_ = glGetUniformLocation(progr, "modelToProjection");
			//emissive_colorIndex_ = glGetUniformLocation(program(), "emissive_color");
		}
	};
}