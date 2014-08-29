#pragma once




#include "Graphic.h"

namespace ANAS {

	
	class ANativeActivity
	{
	};

	class AInputQueue
	{
	};

	class ANativeWindow
	{
	};

	
	class InputActivity;
	class ANativeActivityCallbacks;
	class AConfiguration;
	class ActivityCallbacks {
	public:
		virtual void onConfigurationChanged(ANativeActivity*) = 0;
		virtual void onDestroy(ANativeActivity*) = 0;
		virtual void onStart(ANativeActivity*) = 0;
		virtual void onResume(ANativeActivity*) = 0;
		virtual void onPause(ANativeActivity*) = 0;
		virtual void onStop(ANativeActivity*) = 0;
		virtual void onLowMemory(ANativeActivity*) = 0;


		virtual void onWindowFocusChanged(ANativeActivity*, int focused) = 0;

		virtual void onSaveInstanceState(ANativeActivity*, size_t* outLen) = 0;

		virtual void onNativeWindowCreated(ANativeActivity*, ANativeWindow*) = 0;
		virtual void onNativeWindowDestroyed(ANativeActivity*, ANativeWindow*) = 0;

		virtual void onInputQueueCreated(ANativeActivity*, AInputQueue*) = 0;
		virtual void onInputQueueDestroyed(ANativeActivity*, AInputQueue*) = 0;
	};

	
	class ActivityConfigration {

	public:

		ANativeActivity	*pActivity;

		void	*pSavedState;
		int	SavedStateSize;

		ActivityCallbacks	*pUserCallbacks;
		ANAS::InputActivity	*pInput;
		ANAS::Graphic	*pGraphic;

		ActivityConfigration(){
			pActivity = NULL;
			pSavedState = NULL;
			SavedStateSize = 0;

			pUserCallbacks = NULL;
			pInput = NULL;

		}
	};

	
	class Activity {

	private:
		ActivityCallbacks	*pCallBacks;

		ANAS::InputActivity	*pInputInterface;
		ANAS::Graphic	*pGraphicInterface;

		std::future<void>	DestroyFuture;
		std::promise<void>	DestroyPromise;

		// System
		ANativeActivity	*pActivity;
		void	*pSavedState;
		int	SavedStateSize;
		AConfiguration	*pConfig;

		Activity();


	public:
		Activity(ActivityConfigration &Configration);

		~Activity();

	
		void SetCallBacks(ANativeActivityCallbacks * callbacks);



		// Behavior
		void onConfigurationChanged(ANativeActivity*);
		void onDestroy(ANativeActivity*);
		void onStart(ANativeActivity*);
		void onResume(ANativeActivity*);
		void onPause(ANativeActivity*);
		void onStop(ANativeActivity*);
		void onLowMemory(ANativeActivity*);
		void onWindowFocusChanged(ANativeActivity*, int);
		void onSaveInstanceState(ANativeActivity*, size_t*);
		void onNativeWindowCreated(ANativeActivity*, ANativeWindow*);
		void onNativeWindowDestroyed(ANativeActivity*, ANativeWindow*);
		void onInputQueueCreated(ANativeActivity*, AInputQueue*);
		void onInputQueueDestroyed(ANativeActivity*, AInputQueue*);
	};
}

