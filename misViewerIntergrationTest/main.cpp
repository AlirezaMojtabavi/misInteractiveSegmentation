#include "stdafx.h"


#include "misSegmentationWithBrush.h"

int main(int argc, char* argv[])
{
	int testNUmber;
	std::istringstream seriesNumberStream(argv[3]);
	seriesNumberStream >> testNUmber;
	switch (testNUmber)
	{

	case 1:
	{
		misSegmentationWithBrush imageTest(argc, argv);
		imageTest.Run();
		break;
	}
	}

}
