/*
 *  
 *  $Id: parametrosprincipales.h $
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

#include <api/api.h>
#include <api/autoptr.h>
#include <api/iwizard.h>

#include "pasosexportacionbase.h"
#include "datospersistentesexportacion.h"


namespace GNC {
	namespace GCS {
		class IContratoExportacion;
		class IVista;
		class IEntorno;
	}
	namespace GUI {

		class ParametrosPrincipales: public ParametrosPrincipalesBase,public IPasoWizard
		{
			public:

				ParametrosPrincipales(wxWindow* pParent,IWizard* pWizard, GNC::GCS::Ptr<TipoWizardExportacion> pDatosPersistentes);
				~ParametrosPrincipales();

			protected:			
				GNC::GCS::Ptr<TipoWizardExportacion> m_pDatosPersistentes;

				void OnChoiceFormatoDestino(wxCommandEvent &event);

			public:

				bool Seleccionardirectorio();

				virtual std::string GetTitle();

				virtual std::string GetSubTitle();

				virtual bool Siguiente();

				virtual bool Anterior();

				virtual bool Cancelar();

				virtual bool Validar();
			//endregion

		};
	}
}
