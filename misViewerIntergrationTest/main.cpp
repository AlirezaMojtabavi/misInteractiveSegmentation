#include "stdafx.h"


#include "misSegmentationWithBrush.h"
#include "SegmentationWithBrush4View.h"

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
	case 2:
	{
		SegmentationWithBrush4View segmentation_with_brush4(argc, argv);
		segmentation_with_brush4.Run();
		break;

	}
	}

}
