#pragma once
/*
 *  
 *  $Id: showhistory.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 *
 */
#ifndef IMAGEPRINTTOOL_H
#define IMAGEPRINTTOOL_H
#include "enabled_tools.h"
#include <map>
#include <export/tools/iimageprinttool.h>
#include <api/api.h>
#include <api/autoptr.h>

class wxPrintData;
namespace GNC {

	class EXTAPI ImagePrintTool : public GNC::GCS::IImagePrintTool {

	protected:

	public:
		virtual GNC::GCS::ITool* NewTool();
		ImagePrintTool();
		ImagePrintTool(GNC::GCS::Ptr<wxPrintData>& pPrintData);
		virtual ~ImagePrintTool();

		virtual bool ExecuteAction();
		virtual void AppendToolIn(wxEvtHandler* pParent, wxMenu* pMenu);
		bool IsEnabled();

	protected:
		GNC::GCS::Ptr<wxPrintData> m_pPrintData;

	};
}
#endif
