/*
 *  
 *  $Id: resettool.h $
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
#pragma once

#include <export/tools/iqueryretrievetool.h>
#include <api/api.h>

namespace GNC {

	class EXTAPI QueryRetrieveTool : public GNC::GCS::IQueryRetrieveTool
	{
		public:
		virtual GNC::GCS::ITool* NewTool();
		QueryRetrieveTool();
		~QueryRetrieveTool();

		virtual bool HasDropDownMenu();
		void AppendDropDownMenu(wxEvtHandler* pParent, wxMenu* pMenu);
		
		virtual bool ExecuteAction();
		virtual void AppendToolIn(wxEvtHandler* pParent, wxMenu* pMenu);

		virtual void QueryRetrievePacs();
		virtual void QueryRetrieveCloud();

	protected:

	};
}