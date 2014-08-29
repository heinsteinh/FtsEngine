#include "stdafx.h"
#include "RenderSystem.h"

#include "VariableSystem.h"
#include "CommandSystem.h"



namespace tin {
	RenderSystem::RenderSystem(){

	}

	RenderSystem::~RenderSystem(){
		if (current_renderer_){
			delete current_renderer_;
		}
	}

	void RenderSystem::Init(){
		
		/*CommandSystem::GetInstance().AddCommand("rs_GetCurrentConfig", BIND_COMMAND(RenderSystem::rs_GetCurrentConfig));
		CommandSystem::GetInstance().AddCommand("rs_SetRenderConfig", BIND_COMMAND(RenderSystem::rs_SetRenderConfig));*/

		
		VariableSystem::GetInstance().Set("rs_clear_default_fb", true);
		VariableSystem::GetInstance().Set("rs_ready", false);
		VariableSystem::GetInstance().Set("rs_line_width", 2.0);
		VariableSystem::GetInstance().Set("rs_default_fb", 0);
		VariableSystem::GetInstance().Set("rs_scale_factor", 1.0f);
		VariableSystem::GetInstance().Set("rs_device_orientation", 0);

		is_intialized_ = false;
	}

	void RenderSystem::Shutdown(){
		is_intialized_ = false;
	}

	void RenderSystem::Start(){
		/*
		switch (VariableSystem::GetInstance().GetAsInt("r_renderer")) 
		{
		case kOpenGLES20:
#if OPENGLES20
			current_renderer_ = new OpenGLES20();
#endif
			break;
#if OPENGL3
		case kOpenGL3:
			current_renderer_ = new OpenGL3();
			break;
#endif
		}
		*/

		if (current_renderer_)
		{
			current_renderer_->Init();
			//SetCurrentContext();
			is_intialized_ = true;
		}
		else{
			LoggingSystem::LogError("No renderer initialized!");
		}

	

	}

	void RenderSystem::Stop()
	{
		/*GLProgramManager::Destroy(); */
		current_renderer_->Stop();
	}

	void RenderSystem::QueueRender(RenderDef render_def){
		render_queue_.push_back(render_def);
	}


	void RenderSystem::DrawFrame(){
		if (!tin::VariableSystem::GetInstance().GetAsBool("rs_ready")){
			return;
		}
		current_renderer_->StartFrame();

		//Engine::GetInstance().application()->RenderStart();

		if (load_new_config_){
			//this->LoadRenderConfig(new_config_);
			load_new_config_ = false;
		}

		if (is_intialized_){
			facts_.frames++;;
		}

	}

	void RenderSystem::CopyModel(Model *model, std::function<void(BufferInfo)> call_back){
		/*BufferInfo buffer_info = this->CopyModelToGPU(model);
		call_back(buffer_info);*/
	}

	void RenderSystem::CopyTexture(Texture *texture, std::function<void(int)> call_back){
		int index = this->CopyTextureToGPU(texture);
		call_back(index);
	}

	BufferInfo RenderSystem::CopyModelToGPU(tin::Model *model)
	{
		// LoggingSystem::LogMessage("RC_CopyModelToGPU: %s", model->name());
		
		/*if (model->buffer_info.array_object == -1 && model->buffer_info.buffer_object == -1){
			BufferInfo buffer_info;
			bool result = current_renderer_->CopyModel(model->vertices(), model->num_vertices(), model->indices(), model->num_indices(), buffer_info);

			if (result){
				facts_.objects_loaded++;
			}
			else {
				LoggingSystem::LogError("Error copyModelToGPU");
			}
			return buffer_info;
		}*/
		return BufferInfo();
	}

	void RenderSystem::RemoveModel(BufferInfo buffer_info){
		bool result = current_renderer_->RemoveModelFromMemory(buffer_info);
		if (!result){
			LoggingSystem::LogError("Error removing model: %d", buffer_info.array_object);
		}
		else {
			facts_.objects_loaded--;
		}
	}

	void RenderSystem::RemoveTexture(int index){
		bool result = current_renderer_->RemoveTexture(index);
		if (!result){
			LoggingSystem::LogError("Error removing texture: %d", index);
		}
	}


	int RenderSystem::CopyTextureToGPU(Texture *texture){
		int result = current_renderer_->CopyTexture(texture);
		if (result == -1){
			return -1;
		}
		/*texture->ClearBuffer();
		texture->status(Loaded);
		texture->index(result);*/
		return result;
	}

	void RenderSystem::UpdateViewPort(int width, int height){
		VariableSystem::GetInstance().Set(R_WIDTH, width);
		VariableSystem::GetInstance().Set(R_HEIGHT, height);
		if (current_renderer_){
			current_renderer_->SetViewport(0, 0, width, height);
		}
	}

	void RenderSystem::StopRenderer(){
		current_renderer_->Stop();
	}

	void RenderSystem::StartRenderer(){
		current_renderer_->Init();
	}


	void RenderSystem::RemoveResources(){
		/*ModelManager::SharedInstance()->UnloadAllModels();
		TextureManager::SharedInstance()->UnloadAllTextures();*/
	}

	void RenderSystem::OnResize(int width, int height){
		VariableSystem::GetInstance().Set("rs_ready", false);
		this->UpdateViewPort(width, height);
		this->StopRenderer();
		this->StartRenderer();

		/*for (int i = 0; i < render_config_.NumRenderTargets(); i++){
			current_renderer_->RemoveTexture(render_config_.GetRenderTargetBuffer(i));
		}*/

		ResetRenderResources();
		VariableSystem::GetInstance().Set("rs_ready", true);
	}


	void RenderSystem::ResetRenderResources(){
		int width = VariableSystem::GetInstance().GetAsInt(R_WIDTH);
		int height = VariableSystem::GetInstance().GetAsInt(R_HEIGHT);

		/*for (int i = 0; i < render_config_.NumRenderTargets(); i++){
			RenderTarget target = render_config_.GetRenderTarget(i);
			target.buffer = current_renderer_->CreateRenderTarget(width, height, target.format);
			render_config_.SetRenderTarget(i, target);
		}*/
	}

}