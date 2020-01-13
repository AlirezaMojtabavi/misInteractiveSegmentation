/*
*  
*  $Id: dicombrowsercomponent.h $
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
#include <string>
#include <vector>
#include <set>
#include <ostream>
#include <api/api.h>
#include <api/globals.h>
#include "dicombrowsercomponentbase.h"
#include <api/dicom/imodelodicom.h>


namespace GNC {
	namespace GUI {
		class EXTAPI DicomBrowserComponent: public DicomBrowserComponentBase
		{
		public:
			DicomBrowserComponent(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER);
			~DicomBrowserComponent();

			void SetModel(IModeloDicom& modelo);
			void SetDiagnosticModel(IModeloDicom& modelo);

			void OnDicomDirIzqAddAll(wxCommandEvent& );
			void OnDicomDirDerDelAll(wxCommandEvent& );

			void OnTreeIzqItemActivated(wxTreeEvent& );

			void OnTreeDerItemActivated(wxTreeEvent& );

			void OnAdd(wxCommandEvent& );

			void OnDel(wxCommandEvent&);

			void OnTreeIzqBeginDrag(wxTreeEvent& );

			void OnTreeDerBeginDrag(wxTreeEvent& );

			void AddItemsSeleccionados();

			void AddItemsSeleccionados(wxArrayTreeItemIds& idsSeleccionados);

			void DelItemsSeleccionados();
			void DelItemsSeleccionados(wxArrayTreeItemIds& idsSeleccionados);

			void OnTreeDerItemMenu(wxTreeEvent& event);

			void OnTreeIzqItemMenu(wxTreeEvent& event);

			wxTreeItemId HelperBuscaID(const wxTreeItemId& padre, const wxString& uid);

			void HelperCopiaEnProfundidad(const wxTreeItemId& padreDer, const wxTreeItemId& padreIzq);

			void HelperGetAllPatients(wxTreeListCtrl* pTree, wxArrayTreeItemIds& idsSeleccionados);

			void HelperRellenaPathsDicomDir(const wxTreeItemId& id, std::set<std::string>& listaPaths);
			void HelperRellenaUIDs(const wxTreeItemId& id, std::set<std::string>& seriesSet, bool isDiagnostic);

			std::list<std::string> GetSelectedPaths();
			std::list<std::string> GetSelectedUIDs(bool isDiagnostic);

		protected:
			wxImageList* m_pImageList;
		};
	}
}
