#pragma once

enum misCineDirection
{
	 backwardDirection, //UpToDown
	 forwardDirection   //DownToUp
};

enum TreeSelectedStatus
{
	PatinetIsSelected=0,
	StudyIsSelected,
	SeriIsSelected,
	ImageIsSelected,
	NoneAreSelected,
};

enum PreviewSeriControl
{
	PreviewDisable = 0,
	PreviewEnable,
	PreviewRunning,
};

struct DataUploadingStatuse
{
	bool                ValidTree;
	TreeSelectedStatus  TreeSelectionSataus;
	PreviewSeriControl  PreviewSeriEnable;
};