#pragma  once
enum RGState
{
	OKRG=0,
	WrongROI,
	WrongThreshold
};

struct misRGSeed
{
	int x;
	int y;
	int z;

	misRGSeed()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};