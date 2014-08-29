#pragma once

#ifndef _RenderSystem_H_
#define _RenderSystem_H_

#include <unordered_map>

#include "TSingleton.h"
#include "RenderTypes.h"

#include "CommandSystem.h"
#include "Renderer.h"


namespace tin
{
	class Node;
	class Model;
	class RenderWorld;
	class Texture;

	
	class Texture;
	class RenderModifier;
	class CubeMap;

	class RenderSystem : public CSingleton<RenderSystem>
	{
		friend class CSingleton<RenderSystem>;

	public:
		RenderSystem();
		~RenderSystem();
		void Start();
		void Stop();

		Renderer* CurrentRenderer() { return current_renderer_; };

		void UpdateViewPort(int width, int height);
		void DrawFrame();

		void CopyModel(Model *model, std::function<void(BufferInfo)> call_back);
		void CopyTexture(Texture *texture, std::function<void(int)> call_back);

		void RemoveModel(BufferInfo buffer_info);
		void RemoveTexture(int index);

		void StopRenderer();
		void StartRenderer();

		void OnResize(int width, int height);

		void RemoveResources();
		void ResetRenderResources();

		void QueueRender(RenderDef render_def);
		//RenderConfig CurrentRenderConfig();

		std::list<std::string> ModifierNames();
		//void SetRenderConfig(RenderConfig &config);


		//void AddDebugRay(Ray ray);
		void ClearDebugRays();
		int32_t NumDebugRays();
		//Ray DebugRays(int32_t index);

		void AddRenderModifer(std::string name, RenderModifier *modifier);

		void rs_GetCurrentConfig(Json::Value &json);
		void rs_SetRenderConfig(Json::Value &json);

	private:
		//RenderConfig render_config_;

		Renderer *current_renderer_;
		RendererFacts facts_;
		bool is_intialized_;
		std::unordered_map<std::string, RenderModifier *> render_modifiers_;
		std::list<RenderDef> render_queue_;

		//std::vector<Ray> debug_rays_;

		void Init();
		void Shutdown();

		//void LoadRenderConfig(RenderConfig &config);
		BufferInfo CopyModelToGPU(Model *model);
		void CopyCubemap(CubeMap *cube_map, Texture *left, Texture *right, Texture *top, Texture *bottom, Texture *front, Texture *back);
		int CopyTextureToGPU(Texture *texture);
		uint32_t back_frame_buffer_;

		// Testing, need system to delay and reorder commands in render
		bool load_new_config_;
		//RenderConfig new_config_;

		friend class Singleton;
		friend class DebugSymbol;
	};
} // tin
#endif