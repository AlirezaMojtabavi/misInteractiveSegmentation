#pragma once

enum CommandEnum
{
	vkNoCommand = -1, 
	vkZoonIn, 
	vkZoomOut, 
	vkAcceptYesOk, 
	vkResetNoCancle, 
	vkNextTab, 
	vkPreviousTab, 
	vkNextLandmark,
	vkAutoFindingLandmark,
	vkAutoCapturingLandmark, 
	vkStartSurfaceRegistration,
	vkCalculateSurfaceRegistration,
	vkNextMainImageStatus, 
	vkAutoSnapshotStatus, 
	vkFullScreenStatus,
	Ok,
	Cancel,
	Yes,
	No,
	Abort,
	Retry,
	Ignore,
	vkNone
};

typedef  std::map<int, CommandEnum>					misVirtualRegionTypdef;
typedef  std::map<std::string, misVirtualRegionTypdef>	misSubseqVirtualCmdTypedef;

struct VirtualKeyProprties
{
	int		regionID;
	double	actionValue;

	VirtualKeyProprties()
	{
		Reset();
	}

	void Reset()
	{
		regionID = -1;
		actionValue = 0.0;
	}
};


struct VirtualKeyCommand
{
	CommandEnum			commandRelatedEnum;
	VirtualKeyProprties vkProp;
	//double		actionValue;

	VirtualKeyCommand()
	{
		Reset();
	}
	
	void Reset()
	{
		commandRelatedEnum	= vkNoCommand;
		//actionValue			= 0.0;
	}

	bool operator !=(VirtualKeyCommand right)
	{
		if (this->vkProp.actionValue != right.vkProp.actionValue)
		{
			return true;
		}
		else if (this->vkProp.regionID != right.vkProp.regionID)
		{
			return true;
		}
		else if (this->commandRelatedEnum != right.commandRelatedEnum)
		{
			return true;
		}

        return false;
	};
};
