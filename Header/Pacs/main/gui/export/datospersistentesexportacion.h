/*
 *  
 *  $Id: datospersistentesexportacion.h $
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

#include <api/dicom/idicom.h>
#include <export/contracts/iimageexportcontract.h>

namespace GNC {
	namespace GCS {
		class IVista;
	}
}

namespace GNC {
	namespace GUI {
		typedef enum {DICOM, BMP, JPEG, PNG} FormatoDestino;

		typedef struct TipoWizardExportacion{
			typedef enum {EXTERNAL_FOLDER, OVERWRITE, NEW_STUDY} Target;
			Target		  m_target;
			std::string   m_pathDestino;


			GNC::GCS::Ptr<GNC::GCS::IImageExportDelegate> m_pExportDelegate;
			std::list<long> ListOfSeriesPks;
			//parametros principales
			FormatoDestino m_formatoDestino;
			bool m_ficheroActual;

			//exportacion ginkgo
			GIL::DICOM::DicomDataset m_base;
			bool m_incluirTagsGinkgo;

			//imagenes
			bool m_incluirWidgets;
			typedef GNC::GCS::IImageExportDelegate::TValorationMaps MapaMapasValoracion;
			MapaMapasValoracion m_mapasValoracion;

			//jpeg
			int m_jpegCalidad;
			
			TipoWizardExportacion() :
					m_target(EXTERNAL_FOLDER),
					m_pathDestino(),
					m_pExportDelegate(),
					ListOfSeriesPks(),
					m_formatoDestino(DICOM),
					m_ficheroActual(true),
					m_base(),
					m_incluirTagsGinkgo(true),
					m_incluirWidgets(false),
					m_mapasValoracion(),
					m_jpegCalidad(95)
			{
			}

			~TipoWizardExportacion(){
				m_mapasValoracion.clear();
			}

		} TipoWizardExportacion;
	}
}
