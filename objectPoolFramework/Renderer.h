
#ifndef _Renderer_H_
#define _Renderer_H_



#include "RenderTypes.h"
namespace tin
{
	typedef unsigned short GL_INDICES;
	struct Vertex;
	class Shader;
	class Model;
	class Texture;

	class Renderer
	{
	public:
		virtual ~Renderer() { };
		virtual void Init() = 0;
		virtual void Stop() = 0;

		virtual void StartFrame() = 0;
		virtual void EndFrame() = 0;


		//virtual void ClearBufferWithColor(glm::vec4 color, bool color_bit, bool depth_bit, bool stencil_bit) = 0;

		virtual bool CopyModel(const Vertex* vertices, const int num_vertices, const GL_INDICES* triangles, const int num_indices, BufferInfo &buffer_info) = 0;
		virtual bool RemoveModelFromMemory(BufferInfo buffer_info) = 0;

		virtual int CopyTexture(Texture *texture) = 0;
		virtual int CopyCubemap(Texture *left, Texture *right, Texture *top, Texture *bottom, Texture *front, Texture *back) = 0;
		virtual bool RemoveTexture(int texture_id) = 0;

		virtual void SetViewport(int x, int y, int width, int height) = 0;

		virtual void BindVertexArray(int index) = 0;

		virtual void DrawElements(DrawType type, int num_indices, void* indices) = 0;

		virtual void SetScissorRegion(int x, int y, int width, int height) = 0;
		virtual void SetScissorEnabled(bool enabled) = 0;

		virtual void SetDepthTest(bool enabled) = 0;
		virtual void SetWriteMask(bool r, bool g, bool b, bool a) = 0;
		virtual void SetDepthMask(bool d) = 0;
		virtual void SetCulling(CullingMode mode) = 0;
		virtual void SetCulling(bool enabled) = 0;

		virtual void SetDepthFunc(DepthFunction function) = 0;
		virtual void SetBlending(bool enabled) = 0;
		virtual void SetBlendMode(BlendMode source_factor, BlendMode dest_factor) = 0;

		virtual void SetLineWidth(float width) = 0;

		virtual void SetTexture(int texture) = 0;
		virtual void BindTexture(int index) = 0;

		virtual void BindFrameBuffer(uint32_t frame_buffer) = 0;
		virtual void SetDrawBuffers(int count) = 0;
		virtual uint32_t CreateFrameBuffer() = 0;
		virtual uint32_t CreateRenderTarget(int width, int height, RenderTargetFormat format) = 0;

		virtual void AddRenderTargetToFrameBuffer(uint32_t render_target, uint32_t frame_buffer, FrameBufferAttachment attachment) = 0;
		virtual void RemoveRenderTargetFromFrameBuffer(uint32_t render_target, uint32_t frame_buffer, FrameBufferAttachment attachment) = 0;

		virtual void DestroyFrameBuffer(uint32_t) = 0;
		virtual void DestroyRenderTarget(uint32_t) = 0;

		virtual bool CheckRenderError(std::string function_name) = 0;
		virtual bool CheckFrameBuffer() = 0;

		virtual uint32_t DefaultFrameBuffer(){ return default_framebuffer_; };
	protected:
		uint32_t default_framebuffer_;
		uint32_t default_colorbuffer_;
		uint32_t default_depthbuffer_;
	};
} // tin
#endif