/*
 *  
 *  $Id: dialogoadquisicion.h $
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
#include <list>

#include <api/autoptr.h>
#include <api/controllers/imodulecontroller.h>
#include <api/imodelointegracion.h>
#include <api/observers/ieventsobserver.h>

#include <main/controllers/pacscontroller.h>
#include <commands/comandopacs.h>

#include "dialogoadquisicionbase.h"

class IModeloDicom;
class wxAnimationCtrl;

namespace GNC {

	namespace GUI {

		class DialogoAdquisicion: public DialogoAdquisicionBase, public GADAPI::PACS::IComandoPACSNotificador, public GNC::GCS::IEventsObserver
		{
			public:
				static DialogoAdquisicion* Instance();
				static void FreeInstance();

				DialogoAdquisicion(wxWindow* pParent);
				~DialogoAdquisicion();
				
				virtual bool Show(bool show = true);
				virtual bool Show(const std::string& idPatient, const std::string& idPACS);

			//---------------------------------------------------------------------------
			//region Eventos de interfaz
				virtual void OnPACSChanged(wxCommandEvent & event);
				virtual void OnKeyDownFormulario( wxKeyEvent& event );
				virtual void OnFechaDesdeDateChanged( wxDateEvent& event );
				virtual void OnFechaHastaDateChanged( wxDateEvent& event );
				virtual void OnBusquedaClick( wxCommandEvent& event );
				virtual void Search();
				virtual void OnCancelClick( wxCommandEvent& event);
				std::string GetModalities();
				virtual void OnLimpiarClick( wxCommandEvent& event );
				virtual void OnCloseClick( wxCommandEvent& event );
				virtual void OnDescargarClick( wxCommandEvent& event);
				virtual void OnLinkClick( wxCommandEvent& event);

				virtual void OnTreeSelChanged(wxTreeEvent& event);
				virtual void OnTreeItemActivated(wxTreeEvent& event);
				virtual void OnTreeItemMenu(wxTreeEvent& event);
				virtual void OnTreeItemExpanded(wxTreeEvent& event);
				virtual void OnTreeBeginDrag(wxTreeEvent& event);
				virtual void OnClickColumnHeader(wxListEvent& event);
			
			//---------------------------------------------------------------------------
			//region Helpers
			std::string GetServerSeleccionado();
			bool IsLinkSupported();
			void AddDescarga(bool link = false);
			void ShowProperties();
			bool IsAllowedToDownload(const std::string& modality);
			void ShowAnimation(bool show);
			
			void LimpiarBusquedas(bool lock = true);
			//endregion

			//---------------------------------------------------------------------------
			//region realizacion de la interfaz IComandoPACSNotificador
			virtual void PACSCargarListado(IModeloDicom *);
			//endregion

			//para enterarse si ha parado un comando...
			virtual void ProcesarEvento(GNC::GCS::Events::IEvent *evt);
			//

			/** Init download **/
			bool AddDownload(const std::string& server, const std::string& modality, bool seriesMode, const std::string& studyUID, const std::string& seriesUID, bool link);

			private:
				static DialogoAdquisicion* m_pInstance;

				wxString m_SelectedPACS;
				
				wxAnimationCtrl* m_pAnimation;

				GIL::DICOM::ContextoResultado* m_pResultado;
				wxImageList*                   m_pImageList;
				GADAPI::ComandoPACS*           m_pComandoPACS;
				wxTreeItemId                   m_lastExpanded;
				GNC::GCS::Ptr<IModeloDicom>    m_pModeloDicom;

				bool        m_SizeRestriction;
				bool        m_SizeOK;
				bool        m_reverseOrder;


				typedef enum TDialogMode
				{
					TD_SERIES,
					TD_STUDIES
				}TDialogMode;
				TDialogMode m_Mode;

				GNC::GCS::ILockable m_TreeListResultadosLocker; // Necesario para evitar problemas con el treelistcontrol.

				typedef std::list<wxCheckBox*>  TModalitiesVector;
				TModalitiesVector m_modalitiesList;
				DicomServerList::TServerList ListOfServers;

		};
	}
}
