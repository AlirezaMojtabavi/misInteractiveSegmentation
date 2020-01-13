/*
 *  
 *  $Id: procesarcalibrado.h $
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
#include <commands/inotificadorcalibrado.h>
#include "pasoscalibradobase.h"
#include <api/controllers/iprogresscontroller.h>

#include <string>
#include <vector>

namespace GNC {
    namespace GCS {
        class IComando;
    }
}

namespace GNC {

	namespace GUI {

		struct TipoWizardCalibrado;

		class ProcesarCalibrado: public ProcesarCalibradoBase, public IPasoWizard, public GADAPI::INotificadorCalibrado,GNC::INotificadorProgreso
		{
			public:
				ProcesarCalibrado(wxWindow* pParent,IWizard* pWizard,TipoWizardCalibrado* pDatosPersistentes);
				~ProcesarCalibrado();

				void SetPuntosCalibrado(std::list<GNC::GUI::TPuntoCalibrado>& puntos);
				virtual bool NotificarProgreso(float progresoNormalizado, const std::string& texto);


			protected:

				void OnRefrescoProgreso(wxCommandEvent& evt);

				TipoWizardCalibrado* m_pDatosPersistentes;
				bool m_Ok;
				GNC::GCS::IComando *m_pCmd;


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

				DECLARE_EVENT_TABLE()

		};
	}
}
