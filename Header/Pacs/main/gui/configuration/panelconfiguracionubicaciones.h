/*
 *  
 *  $Id: panelconfiguracionubicaciones.h $
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
#include <api/iconfiguracion.h>
#include "panelesconfiguracionginkgobase.h"
#include <string>
#include <vector>

namespace Ubicaciones {
	class UbicacionesGridTable;
}

namespace GNC {
	namespace GUI {

		class PanelConfiguracionUbicaciones: public PanelConfiguracionUbicacionesBase, public IPasoConfiguracion
		{
			public:
				PanelConfiguracionUbicaciones(wxWindow* pParent,IDialogoConfiguracion* pDialogo);
				~PanelConfiguracionUbicaciones();

				void Recargar();

				//region "Metodos de IPasoConfiguracion"
				wxWindow* GetPanel();

				std::string GetTitle();

				std::string GetCabecera();

				bool Validar();

				bool Guardar();
				//endregion

				//region "Helpers"
				void AutoSizeGrid();
				//endregion

			public:
				Ubicaciones::UbicacionesGridTable* m_pUbicacionesGridTable;


			protected:
				
				virtual void OnGridDClick( wxGridEvent& event );
				virtual void OnGridSelectionChanged(wxGridRangeSelectEvent& event);
				virtual void OnNuevoClick( wxCommandEvent& event );
				virtual void OnEditarClick( wxCommandEvent& event );
				virtual void OnEliminarClick( wxCommandEvent& event );
				virtual void OnHelpClick(wxMouseEvent &event);
				virtual void OnSize( wxSizeEvent& event );
		};
	}
}
