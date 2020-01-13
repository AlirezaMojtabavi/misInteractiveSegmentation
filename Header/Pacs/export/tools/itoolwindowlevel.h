#pragma once
/*
*  
*  $Id: itoolwindowlevel.h $
*  Ginkgo CADx Project
*
*  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
*  http://ginkgo-cadx.com
*
*  This file is licensed under LGPL v3 license.
*  See License.txt for details
*
*/
#ifndef IWINDOWLEVELTOOL_H
#define IWINDOWLEVELTOOL_H
#include <api/toolsystem/iwidgettool.h>
#include <export/contracts/iwindowlevelcontractable.h>
#include "iherramientascore.h"

namespace GNC {
	namespace GCS {

		class EXTAPI IToolWindowLevel: public IWidgetTool, public IWindowLevelContractable 
		{
		public:
			static GNC::GCS::ITool::UID ID;
			IToolWindowLevel();			
		};
	}
}
#endif