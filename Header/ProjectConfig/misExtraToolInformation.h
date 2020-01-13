#pragma once

#include "misRegistrationEnums.h"
#include "misTrackedToolEnums.h"

class misExtraToolInformation
{
public:
	void Reset()
	{
		for (int i = 0; i < 20; i++)
		{
			markerStatus[i] = Unset_MarkerStatus;
		}
	}

	misExtraToolInformation()
	{
		this->Reset();
	}

	bool operator == (const misExtraToolInformation &right)
	{
		bool res = true;

		for (int i = 0; i < 20; i++)
		{
			if (right.markerStatus[i] != this->markerStatus[i])
			{
				res = false;
				break;
			}
		}
		return res;
	}

	bool operator !=(const misExtraToolInformation right)
	{
		bool res = !(*this == right);
		return res;
	}
	misMarkerStatus& operator[](std::size_t idx)
	{ 
		return markerStatus[idx]; 
	}

private:

	misMarkerStatus markerStatus[20];



};
