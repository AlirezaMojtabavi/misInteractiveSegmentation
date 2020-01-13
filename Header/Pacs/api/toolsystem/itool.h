#pragma once
/*
 *  
 *  $Id: itool.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 */
#ifndef ITOOL_H
#define ITOOL_H

#include <api/api.h>
#include <api/globals.h>
#include <api/ibutton.h>
#include <api/iexception.h>
#include <wx/bitmap.h>
#include <wx/cursor.h>


#include <wx/bitmap.h>

class wxXmlNode;
class wxPanel;
class wxSizer;
class wxMenu;
class wxAuiToolBar;
class wxEvtHandler;

namespace GNC {
	namespace GCS {
		class IVista;
		class ITool;
		class IToolController;
		class IModuleController;
	}
}

namespace GNC {

	namespace GCS {
		class EventHandlerITool;

		class EXTAPI ITool {
		public:
			typedef enum {
				TFamiliaGlobal,
				TFamiliaVisualizacion,
				TFamiliaMedicion,
				TFamiliaAnotacion,
				TFamiliaChroma,
				TFamiliaVision,
				TMenuArchivo,
				TMenuEdicion,
				TMenuVer,
				TSeriesMenu,
				TMenuHerramientas,
				TMenuHelp,
				TMenuExport,
				TMenuPACSAcquisition,
				TViewOptions
			} TToolFamily;

			typedef unsigned int UID;

			virtual ~ITool();

			//new tool
			ITool(const ITool::UID& uid, const ITool::TToolFamily& familyUID, const std::string& name, const wxBitmap& icon, const int subFamily = 0xFFFFFFFF, const int& priority = 0);

			TToolFamily GetFamily() {
				return FamilyId;
			}

			int GetSubFamily() {
				return SubFamilyId;
			}

			virtual bool AppendsInGlobalMenu() {
				return false;
			}

			virtual bool AppendsInMenu() {
				return true;
			}

			virtual bool AppendsInToolBar() {
				return true;
			}

			virtual bool HasDropDownMenu() {
				return false;
			}

			virtual void AppendToolIn(wxAuiToolBar* pParent);
			virtual void AppendToolIn(wxEvtHandler* pParent, wxMenu* pMenu);
			virtual void AppendDropDownMenu(wxEvtHandler* pParent, wxMenu* pMenu);

			virtual bool IsEnabled();
			virtual void Enable(bool enabled);
			/*If a tool is not ready it wont be attached to any menu*/
			virtual bool IsReady();
			
			virtual bool ExecuteAction() = 0;


			/** Registers the tool in the Tool Registry Container **/
			void RegisterTool();

			/** Sets the Owner module of the tool (the module providing the tool). NULL if CADxCore **/
			void SetOwnerModule(GNC::GCS::IModuleController* pOwner);
			/** Gets the Owner module of the tool (the module providing the tool). NULL if CADxCore **/
			GNC::GCS::IModuleController* GetOwnerModule();

			virtual GNC::GCS::ITool* NewTool() = 0;

			virtual void SetToolBar(GNC::GCS::IToolController* pParent);
			virtual GNC::GCS::IToolController* GetToolBar();

			virtual int GetKeyCode();
			
			ITool::UID ID;
			TToolFamily FamilyId;
			//sirve para meter separadores en los menus dentro de la misma familia
			int	SubFamilyId;
			int Priority;
			std::string Name;
			wxBitmap Icon;
			GNC::GCS::IToolController* m_pParent;
			IModuleController* OwnerModule;
			int KeyCode;
		protected:
			bool Enabled;
			//

		};
	}
}
#endif
