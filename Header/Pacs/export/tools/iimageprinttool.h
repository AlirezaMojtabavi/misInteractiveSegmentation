#pragma once
/*
*  
*  $Id: ishowhistorytool.h $
*  Ginkgo CADx Project
*
*  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
*  http://ginkgo-cadx.com
*
*  This file is licensed under LGPL v3 license.
*  See License.txt for details
*
*/
#ifndef IIMAGEPRINTTOOL_H
#define IIMAGEPRINTTOOL_H
#include <export/contracts/iimageexportcontractable.h>
#include <api/toolsystem/itool.h>
#include "iherramientascore.h"

namespace GNC {
	namespace GCS {
		class EXTAPI IImagePrintTool:  public ITool, public GNC::GCS::IImageExportContractable
		{
		public:
			static GNC::GCS::ITool::UID ID;
			IImagePrintTool();
		};
	}
}
#endif