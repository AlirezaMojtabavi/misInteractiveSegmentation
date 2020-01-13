#pragma once

#include "misEnums.h"
#include "misTypes.h"
#include "misobjectProperitiesEnums.h"

struct ApproachAndModelInformationStrct
{
	misUID packegeUID;
	misUID objectUID;
	misUID objectContainerUID;
	misUID ParentUID;
	misTreeViewType treeViewType;
	mis3DModelRenderingType renderingType;

	ApproachAndModelInformationStrct()
	{
		Reset();
	};

	void Reset()
	{
		packegeUID = "";
		objectUID = "";
		objectContainerUID = "";
		ParentUID = "";
		treeViewType = UnSetItem;
		renderingType = UnSetRenderingType;
	};
};
