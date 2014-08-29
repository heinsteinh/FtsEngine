
#include <Windows.h>
#include <time.h>
#include <chrono>

namespace ANAS {

	
	class Time {
	private:
		float prevTime;

	public:
		Time()
			:prevTime(clock() / (float)CLOCKS_PER_SEC)
		{
		}

	
		inline void AdjustTime(float sec){
			float _now;

			do {
				_now = (clock() / (float)CLOCKS_PER_SEC);
				Sleep((prevTime + sec - _now)*CLOCKS_PER_SEC);
				//usleep((prevTime + sec - _now)*CLOCKS_PER_SEC);				

			} while (prevTime + sec >= _now);

			prevTime = _now;
		}

	};
}