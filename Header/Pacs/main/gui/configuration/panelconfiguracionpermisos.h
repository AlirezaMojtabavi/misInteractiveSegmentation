/*
 *  
 *  $Id: panelconfiguracionpermisos.h $
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

namespace GNC {
	namespace GUI {

		class PanelConfiguracionPermisos: public PanelConfiguracionPermisosBase, public IPasoConfiguracion
		{
			public:
				PanelConfiguracionPermisos(wxWindow* pParent,IDialogoConfiguracion* pDialogo);
				~PanelConfiguracionPermisos();

				void Recargar();

				//region "Metodos de IPasoConfiguracion"
				wxWindow* GetPanel();

				std::string GetTitle();

				std::string GetCabecera();

				bool Validar();

				bool Guardar();
				//endregion


			protected:
				virtual void OnListaPermisosDClick(wxTreeEvent& event);
				virtual void OnListaPermisosChangeSelection(wxTreeEvent& event);

				virtual void OnSetActive(wxCommandEvent &event);

				virtual void OnNuevoClick(wxCommandEvent &event);

				virtual void OnEditarClick(wxCommandEvent &event);

				virtual void OnEliminarClick(wxCommandEvent &event);

				virtual void OnTextoCambiado(wxCommandEvent &event );

				virtual void OnPropiedadCambiada();

				void OnSize(wxSizeEvent &);

				typedef struct TipoProfile{
					std::string nombre;
					std::string xml;
					bool aplicar;
					TipoProfile() :
						aplicar(false)
					{
					}

					TipoProfile(const std::string& _nombre, const std::string& _xml, bool _aplicar) :
						nombre(_nombre),
						xml(_xml),
						aplicar(_aplicar)
					{						
					}
				} TipoProfile;
				typedef std::vector <TipoProfile> TipoListaProfiles;
				TipoListaProfiles m_profiles;
				bool m_permisosCambiados;

		};
	}
}
