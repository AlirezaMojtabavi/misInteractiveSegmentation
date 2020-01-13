/*
 *  
 *  $Id: wxwizardcalibradoginkgo.h $
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
#include <wx/wizardginkgo/wxwizardginkgobase.h>
#include "datospersistentescalibrado.h"
#include <string>
#include <vector>

class vtkImageData;

namespace GNC {
	namespace GUI {
		class wxWidzardCalibradoGinkgo: public wxWizardGinkgoBase
		{

		public:
			wxWidzardCalibradoGinkgo(wxWindow* pParent, GNC::GCS::IVista* pVista, vtkImageData* pImagen,int slice);
			~wxWidzardCalibradoGinkgo();

			bool  IsOK();
			
			float GetHorizontalSpacing();
			float GetVerticalSpacing();

			void OnSize(wxSizeEvent&)
			{
				Layout();
			}

			virtual void OnCancelarClick(wxCommandEvent& event);

			

			virtual void OnSiguienteClick(wxCommandEvent& event);

			virtual void OnAnteriorClick(wxCommandEvent &event);

			void CargarCurrent();

		protected:
			
			typedef std::list<IPasoWizard*> ListaPasos;
			ListaPasos m_ListaPasos;
			ListaPasos::iterator m_currentPaso;
			GNC::GCS::IVista* m_pVista;
			int m_currentPasoIndex;
			bool            m_OK;
			TipoWizardCalibrado m_datosPersistentes;
		};
	}
}
