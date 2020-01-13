/*
 *  
 *  $Id$
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
#include <list>

#include "taskcontrolbase.h"

namespace GNC{
	namespace GUI {
		class TaskControl : public TaskControlBase
		{
		public:
			TaskControl(wxWindow* pParent,const std::list<long>& seriesPk = std::list<long>());
			~TaskControl();

		protected:
			void RefreshTable();
			virtual void OnRefreshClick(wxCommandEvent& event);
			void OnTaskMenu(wxTreeEvent& event);
			void OnRestartTask(wxCommandEvent& event);
			void OnDeleteTask(wxCommandEvent& event);
			void OnDeleteAll(wxCommandEvent& event);
			std::list<long> m_seriesPk;
		};
	};
};
