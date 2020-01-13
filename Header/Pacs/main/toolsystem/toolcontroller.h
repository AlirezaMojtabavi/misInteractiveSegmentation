#pragma once
/*
 *  
 *  $Id: toolcontroller.h $
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
#ifndef TOOLCONTROLLER_H
#define TOOLCONTROLLER_H
#include <api/api.h>
#include <api/autoptr.h>
#include <api/toolsystem/itoolcontroller.h>

// Forward declarations
namespace GNC {
	namespace GCS {
		class IWidgetTool;
	}
}

namespace GNC {
	namespace GUI
	{
		class wxEventHandlerToolController;
	}
		
	class EXTAPI ToolController : public GNC::GCS::IToolController
	{
	public:
		
		ToolController();

		virtual ~ToolController();

		virtual void InitializeToolController();
		virtual void ReconnectToolController();
		void FinalizeToolController();

		virtual void AddTool(long idTool, GNC::GCS::IContract* pContract);
		virtual void RemoveTool(long idTool);

		virtual GNC::GCS::ITool* GetTool(long idTool);
		virtual void Enable(long idTool, bool enabled);

		virtual wxWindow* CreateNewToolBar(wxWindow* pParent, bool alignLeft = true);
		virtual wxWindow* CreateNewToolBar(wxWindow* pParent, GNC::GCS::ITool::TToolFamily family, bool alignLeft = true);
		virtual wxWindow* CreateNewToolBar(wxWindow* pParent, const TIdList& toolsToInclude, bool alignLeft = true);
		virtual void AppendsToolInMenu(wxEvtHandler* pParent, wxMenu* pMenu, GNC::GCS::ITool::TToolFamily family);
		virtual void AppendsToolsInToolBar(wxAuiToolBar* pToolBar, GNC::GCS::ITool::TToolFamily family);
		virtual void AppendsToolsInToolBar(wxAuiToolBar* pToolBar, const GNC::GCS::IToolController::TIdList& toolsToInclude);

		virtual void OnKeyAccelerator(GNC::GCS::Events::EventoTeclado& evento, wxWindow* pWindow);

		virtual void ActivateTool(long idTool, const GNC::GCS::TriggerButton& buttonmask, wxWindow* pParent);
		virtual void DoActivateTool(long idTool, const GNC::GCS::TriggerButton& buttonmask, wxWindow* pParent);
		virtual void AppendDropDownMenu(long idTool, wxEvtHandler* pParent, wxMenu* pMenu);

		virtual GNC::GCS::IWidgetTool* GetLeftTool();
		virtual GNC::GCS::IWidgetTool* GetRightTool();

		typedef std::map<long, GNC::GCS::ITool*> TToolMap;
		TToolMap m_tools;
		GNC::GCS::IWidgetTool* m_leftTool;
		GNC::GCS::IWidgetTool* m_rightTool;
		GNC::GCS::Ptr<GNC::GUI::wxEventHandlerToolController> EventHandler;

	};
}
#endif
