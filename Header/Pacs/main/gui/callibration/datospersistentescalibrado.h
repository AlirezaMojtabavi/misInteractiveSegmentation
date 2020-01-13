/*
 *  
 *  $Id: datospersistentescalibrado.h $
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

namespace GNC {
	namespace GCS {
		class IVista;
	}
}


namespace GNC {
	namespace GUI {
		typedef struct TPuntoCalibrado{
			float x;
			float y;
			TPuntoCalibrado(){
				x=0.0f;
				y=0.0f;
			}
			TPuntoCalibrado(float valx, float valy){
				x = valx;
				y = valy;
			}
		} TPuntoCalibrado;

		typedef struct TipoWizardCalibrado{
			vtkImageData* m_pImageData;
			
			typedef std::list<TPuntoCalibrado> TVectorPuntos;
			
			int m_slice;
			GNC::GCS::IVista* m_pVista;
			float m_spacingHorizontal;
			float m_spacingVertical;
			TVectorPuntos m_Puntos;			

			TipoWizardCalibrado(){
				m_pImageData = NULL;
				m_spacingHorizontal = -1;
				m_spacingVertical = -1;
				m_slice = 0;
				m_pVista = NULL;
			}

			~TipoWizardCalibrado(){
				m_pImageData=NULL;
				m_Puntos.clear();
			}

		} TipoWizardCalibrado;
	}
}
