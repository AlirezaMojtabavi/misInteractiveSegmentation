/*
*  
*  $Id: comandopacs.h $
*  Ginkgo CADx Project
*
*  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
*  http://ginkgo-cadx.com
*
*  This file is licensed under LGPL v3 license.
*  See License.txt for details
*
*/
#pragma once
//#define _GINKGO_TRACE
#include <api/globals.h>
#include <api/icommand.h>
#include <api/ivista.h>
#include <api/dicom/imodelodicom.h>
#include <api/controllers/ipacscontroller.h>

#include <main/controllers/dcmtk/dicomservers.h>



namespace GIL{
	class IModeloIntegracion;
	namespace DICOM{
		class IPACSController;
	}
}

namespace GADAPI {

	namespace PACS {
		class MISDLLEXPORT IComandoPACSNotificador{
		public:
			virtual ~IComandoPACSNotificador() {}

			virtual void PACSCargarListado(IModeloDicom* pModelo) = 0;
		};
	}

	class MISDLLEXPORT ComandoPACSParams : public GNC::GCS::IComandoParams {

	public:
		typedef enum TipoAmbito {
			TA_Paciente,
			TA_Estudio,
			TA_Serie,
			TA_Imagen,
			TA_NotSpecified
		} TipoAmbito;

		ComandoPACSParams(const std::string& pacienteID, const std::string& pacienteNombre, const std::string& studyUID,
			const std::string& estudioAccNumber, const std::string& estudioModalidad, const std::string& estudioFechaDesde,
			const std::string& estudioFechaHasta, const std::string& studyTimeFrom, const std::string& studyTimeTo, const std::string& serverSeleccionado,
			TipoAmbito ambito, GNC::GCS::Ptr<IModeloDicom> pModeloDicom, GADAPI::PACS::IComandoPACSNotificador* pNotificador) ;

		virtual ~ComandoPACSParams();

	public:
		std::string              m_pacienteID;
		std::string              m_pacienteNombre;
		std::string              m_accessionNumber;;
		std::string              m_estudioModalidad;
		std::string              m_estudioFechaDesde;
		std::string              m_estudioFechaHasta;
		std::string					 m_studyTimeFrom;
		std::string					 m_studyTimeTo;
		std::string					 m_studyUID;

		std::string              m_serverSeleccionado;
		bool                     m_informar;

		TipoAmbito               m_Ambito;
		std::string              m_error;

		GADAPI::PACS::IComandoPACSNotificador* m_pNotificador;
		GNC::GCS::Ptr<IModeloDicom> m_pModelo;
	};



	class MISDLLEXPORT ComandoPACS : public GNC::GCS::IComando {
	public:
		ComandoPACS(ComandoPACSParams* pParams);

    protected:
		virtual void Execute();
		virtual void Update();

    public:
		virtual bool NotificarProgreso(float progresoNormalizado, const std::string &texto);

		void LiberarRecursos();

		ComandoPACSParams* m_pPACSParams;
	};
}
