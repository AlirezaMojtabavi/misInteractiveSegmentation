/*
 *  
 *  $Id: selecciontexto.h $
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
#include "selecciontextobase.h"
#include "../wnota.h"

namespace GNC {
	namespace GCS {
		namespace Widgets {
			namespace Dialogos {
				class SeleccionTexto : public SeleccionTextoBase {
				public:
					typedef GNC::GCS::Widgets::WCajaTexto TWidget;
					typedef GNC::GCS::IWidgetsManager TManager;

					SeleccionTexto(wxWindow* parent, TWidget* pWidget, TManager* pManager);
					~SeleccionTexto();

					virtual void OnClickEnMenu(wxCommandEvent& event);

				protected:

					virtual void OnDialogoKeyDown( wxKeyEvent& event );

					virtual void OnControlTextoKeyDown( wxKeyEvent& event );

					virtual void OnControlTextoTextoActualizado( wxCommandEvent& event );

					virtual void OnBotonCancelarClick( wxCommandEvent& event );

					virtual void OnBotonAceptarClick( wxCommandEvent& event );

					virtual void OnColorCambiado(wxColourPickerEvent& event);

					virtual void OnActivar(wxActivateEvent &event);

					void IniciarColores();

					void Actualizar(bool actualizarWidget = true);

					TWidget*   m_pWidget;
					TManager*  m_pManager;

					wxColour    m_ColorFondo; // Color del fondo del campo de texto. Se cambia automaticamente a fin de leerlo correctamente.
				};
			}
		}
	}
}
