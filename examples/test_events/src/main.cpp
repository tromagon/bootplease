#include "Iw2D.h"
#include "tests.h"

#define FRAME_TIME  (30.0f / 1000.0f)

int main()
{
	Iw2DInit();

	const EventDispatcherTest* tests = new EventDispatcherTest();

	while (!s3eDeviceCheckQuitRequest())
    {

		Iw2DSurfaceClear(0xff000000);

		Iw2DSurfaceShow();
		
		s3eDeviceYield(0);
	}

	delete tests;

	Iw2DTerminate();

	return 0;
}