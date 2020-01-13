#pragma once

struct misShort3DModelViewingStrct
{
	std::string name;
	misUID objectUID;
	misUID objectContainerUID;
	misUID parentImageUID;
	double opacity;
	double volume;
	mis3DModelTypes  type;
	mis3DModelRenderingType renderingType;
	misColorStruct   color;
	bool useable;
	bool visibility3D = false;	
	bool segmentedObjectVisibility;		
	bool objectMarginAlarm;
	bool objectShowMargin;
	double objectMarginValue;

	void Reset()
	{
		name = "";
		objectUID = "";
		objectContainerUID = "";
		parentImageUID = "";
		opacity = 0.0;
		volume = 0.0;
		type = UnSetModelType;
		renderingType = UnSetRenderingType;
		color.InVisible();
		useable = false;
		visibility3D = false;
		segmentedObjectVisibility = false;
		objectMarginAlarm = false;
		objectShowMargin = false;
		objectMarginValue = -1;
	};
	misShort3DModelViewingStrct()
	{
		Reset();
	};
	void operator =(misShort3DModelViewingStrct right)
	{
		name = right.name;
		objectUID = right.objectUID;
		objectContainerUID = right.objectContainerUID;
		parentImageUID = right.parentImageUID;
		opacity = right.opacity;
		volume = right.volume;
		type = right.type;
		renderingType = right.renderingType;
		color = right.color;
		useable = right.useable;
		visibility3D = right.visibility3D;
		segmentedObjectVisibility = right.segmentedObjectVisibility;
		objectMarginAlarm = right.objectMarginAlarm;
		objectShowMargin = right.objectShowMargin;
		objectMarginValue = right.objectMarginValue;
	};
};
