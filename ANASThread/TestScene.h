#pragma once



#include "SceneBase.h"



namespace test {

	
	class testScene : public ANAS::SceneBase 
	{
	private:
		float theta;


	public:

		testScene();
		~testScene();

		// virtual
		void Init();
		void Process();
		void Render();
	};
}

