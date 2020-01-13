/*
 *  
 *  $Id: editordicom.h $
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
#include "editordicombase.h"
#include <api/iwizard.h>
#include <api/ivista.h>
#include <api/controllers/ipacscontroller.h>


#include <string>
#include <vector>

namespace GNC {
	namespace GUI {

		class EditorDICOM: public EditorDICOMBase
		{
			public:
				EditorDICOM(wxWindow* pParent,std::string pathActivo, GIL::DICOM::IPACSController* pImportacion);

				EditorDICOM(wxWindow* pParent,GIL::DICOM::DicomDataset& base, GIL::DICOM::IPACSController* pImportacion);
				~EditorDICOM();

				void GetTagsEditados(GIL::DICOM::DicomDataset & base);

			protected:
				std::string m_ruta;
				GIL::DICOM::DicomDataset m_base;
				wxString m_valorAnonimizado;


				void OnCheckAnonimizar(wxCommandEvent &event);

				void OnCheckNombreApellidos(wxCommandEvent &event);

				void OnCheckIdPaciente(wxCommandEvent &event);

				void OnCheckInstituciones(wxCommandEvent &event);

				void OnCheckComentarios(wxCommandEvent &event);

				void OnCheckConfiguracion(wxCommandEvent &event);

				void Anonimizar(std::string& clave, bool anonimizar);

				void OnPropertyChanged(wxPropertyGridEvent& event);

				void OnPropertyDobleClick(wxPropertyGridEvent& event);

		};
	};
};
