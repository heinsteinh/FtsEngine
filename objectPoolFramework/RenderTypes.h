
#ifndef Engine_RenderTypes_h
#define Engine_RenderTypes_h

#include <vector>
#include <string>
#include <cstdint>
#include <list>


namespace tin {
	class Viewport;
	class RenderModifier;
	typedef enum {
		ALPHA,
		RGB,
		RGBA,
		LUMINANCE,
		LUMINANCE_ALPHA,
		DEPTH24_STENCIL8,
		RGB16,
		NUM_FORMATS
	} RenderTargetFormat;

	typedef enum{
		CullingFront,
		CullingBack,
		CullingFrontAndBack
	} CullingMode;

	typedef enum{
		BlendZero = 0,
		BlendOne = 1,
		BlendDstColor,
		BlendSrcAlpha,
		BlendOneMinusSrcAlpha
	} BlendMode;

	typedef enum {
		DEPTH_FUNC_NEVER,
		DEPTH_FUNC_LESS,
		DEPTH_FUNC_EQUAL,
		DEPTH_FUNC_LEQUAL,
		DEPTH_FUNC_GREATER,
		DEPTH_FUNC_NOTEQUAL,
		DEPTH_FUNC_GEQUAL,
		DEPTH_FUNC_ALWAYS
	} DepthFunction;

	typedef enum{
		Texture2D,
		CubeMapXPositive,
		CubeMapXNegative,
		CubeMapYPositive,
		CubeMapYNegative,
		CubeMapZPositive,
		CubeMapZNegative
	} TextureTarget;

	typedef enum{
		Color0,
		Color1,
		Color2,
		Color3,
		Color4,
		Color5,
		Color6,
		Color7,
		Color8,
		Color9,
		Color10,
		Color11,
		Color12,
		Color13,
		Color14,
		Color15,
		Color16,
		Color17,
		Color18,
		DepthStencil
	} FrameBufferAttachment;

	typedef enum{
		LightTypePoint,
		LightTypeDirectional,
		LightTypeSpotlight,
		LightTypeAmbient
	} LightType;

	typedef enum {
		POINTS,
		LINES,
		LINE_LOOP,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	} DrawType;

	typedef struct RenderTarget{
		RenderTarget() : buffer(0), format(RGB) { }
		std::string name;
		RenderTargetFormat format;
		uint32_t buffer;
	} RenderTarget;

	typedef struct RenderLayer{
		bool clear;
		bool write_depth;
		bool write_color;
		std::string name;
		std::string modifier;
		std::string depth_stencil_target;
		std::vector<std::string> render_targets;
		std::vector<std::string> inputs;
	} RenderLayer;

	typedef struct{
		unsigned int draw_calls;
	} FrameFacts;

	typedef struct RendererFacts{
		RendererFacts() : objects_loaded(0), frames(0) { };
		unsigned int objects_loaded;
		unsigned long frames;
		FrameFacts last_frame;
	} RendererFacts;

	typedef struct RenderSurface{
		RenderSurface() : textured(false), buffer_index(-1), indices(0) { };
		//glm::mat4 model;

		int buffer_index;
		int indices;
		std::vector<int> texture_indexes;
		bool textured;
		float tex_offset_u, tex_offset_v, tex_scale_u, tex_scale_v;
		//glm::mat4 bounding_box_matrix;
	} RenderSurface;

	typedef struct LightDef{
		//glm::vec4 position;
		//glm::quat rotation;
		//glm::vec4 color;
		//LightType type;
		//glm::mat4 model;
		//glm::vec4 attenuation;
	} LightDef;

	typedef struct RenderView{
		//glm::mat4 projection;
		//glm::mat4 view;
		//glm::vec4 view_position;
		//glm::vec4 world_view_position;
		std::list<RenderSurface> surfaces;
		std::vector<LightDef> light_defs;
	} RenderView;

	typedef struct RenderDef{
		RenderView *render_view;
		std::string viewport;
	} RenderDef;


	typedef struct BufferInfo_
	{
		BufferInfo_() : array_object(-1), buffer_object(-1), element_buffer_object(-1) { };

		int array_object;
		int buffer_object;
		int element_buffer_object;
	} BufferInfo;

}

#endif