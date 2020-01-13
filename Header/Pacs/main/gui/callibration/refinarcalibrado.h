/*
 *  
 *  $Id: refinarcalibrado.h $
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
#include <api/iwizard.h>
#include <api/ivista.h>
#include "pasoscalibradobase.h"
#include <api/ievento.h>

#include <string>
#include <vector>

namespace GNC {
	namespace GCS {
		namespace Widgets {
			class WTrapezoideBuilder;
		};
	};

	namespace GUI {
		struct TipoWizardCalibrado;

		class RefinarCalibrado: public RefinarCalibradoBase,public IPasoWizard,public GNC::GCS::Events::ISubscriptorEventos
		{
			public:
				RefinarCalibrado(wxWindow* pParent,IWizard* pWizard,TipoWizardCalibrado* pDatosPersistentes);
				~RefinarCalibrado();

			protected:
				TipoWizardCalibrado*       m_pDatosPersistentes;
				GNC::GCS::IWidgetsManager* m_pWidgetsManager;
				WidgetRepresentation*      m_pWidgetsRepresentation;
				GNC::GCS::Widgets::WTrapezoideBuilder* m_pTrapezoideBuilder;

				void OnMouseEvents(GNC::GCS::Events::EventoRaton& evento);

				void OnKeyDown(GNC::GCS::Events::EventoTeclado& evento);

			//region "Metodos heredados de IPasoWizard"
				virtual bool Attach();

				virtual bool Detach();

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
