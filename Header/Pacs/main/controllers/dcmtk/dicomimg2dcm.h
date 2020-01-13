/*
 *  
 *  $Id: dicomimg2dcm.h $
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
#include <api/globals.h>
#include <api/dicom/idicomizador.h>
#ifdef verify
#define MACRO_QUE_ESTORBA verify
#undef verify
#endif

#include <dcmtk/config/osconfig.h>
#include "libi2d/document2dcm.h"
#include "libi2d/d2dsource.h"
#include "libi2d/i2doutpl.h"
#include "dcmtk/dcmdata/dcdict.h"
#include "dcmtk/dcmdata/dchashdi.h"

class DcmElement;
class wxCSConv;

namespace GIL {
	namespace DICOM {
		
		class DICOMImg2DCM : public IDICOMImg2DCM {
		public:
			/* Constructor */
			DICOMImg2DCM();
			
			/* Destructor */
			~DICOMImg2DCM();
			
			void LiberarMemoria();
			
			/* Inicializa una conversión. IInspectCallback sirve para especificar un callback mediante el cual se pueden inspeccionar los atributos buscados.
			 *
			 * Formatos de entrada soportados:
			 *	  JPEG
			 * Formatos de salida soportados (DICOM SOP a generar):
			 *   VLP (Visible Light Photography)
			 *   SC (Secondary Capture)
			 *   NSC (New Secondary Capture)
			 */
			virtual void Inicializar(std::string& inputFile, IInspectCallBack* pICallback = NULL, bool debug = false, TDICOMOutputFormat outputFormat = TDOF_AUTO);

			virtual void Inicializar(TImageFile& fileDefinition, IInspectCallBack* pICallback = NULL, bool debug = false, TDICOMOutputFormat outputFormat = TDOF_VLP);

			void Inicializar(D2DSource* plugEntrada, IInspectCallBack* pICallback, bool debug, TDICOMOutputFormat outputFormat);
			
			virtual int InsertarJerarquia(DicomDataset& base); 

			virtual int InsertarTagsPrivados(TipoPrivateTags& base);

			virtual int InsertarTagsPrivados(TipoPrivateTags& base, DcmDataset* dcmDataSet);

			int InsertarJerarquia(DicomDataset& base,DcmDataset* dcmDataSet, DcmItem* itemPadre, DcmSequenceOfItems* seqPadre);
			
			/* Actualiza los campos DICOM a sobreescribir */
			virtual void ActualizarCampos(IInspectCallBack* pICallback);
			
			/* Realiza una conversión ya inicializada */
			virtual bool Convertir(std::string& outputFile);

			unsigned int GetElementIdentifier(GIL::DICOM::TipoPrivateTags& tags, DcmDataset* dataset);

			bool CrearSRDoc(std::string& outputFile, DicomDataset& base, std::list<GNC::GCS::Ptr<TipoPrivateTags> >& tagsPrivados);

			virtual void Reset() {
				LiberarMemoria();
			}
			
		protected:
			
			/* Crea un elemento de DCMTK parseando la cadena pasada como parámetro que debe tener el formato:
			 <hex_2_bytes>|<hex_2_bytes>
			 o bien:
			 <hex_2_bytes>|<hex_2_bytes>=<cadena>
			 Nota: <cadena> puede ser vacía
			 */
			DcmElement* CrearElementoConValor(const char* s);
			
			// Main class for controlling conversion
			Document2Dcm*       i2d;
			// Output plugin to use (ie. SOP class to write)
			I2DOutputPlug*   outputPlug;
			// Input plugin to use (ie. file format to read)
			D2DSource*    inputPlug;
			// Result object
			DcmDataset*      resultObject;
			// The transfersytanx proposed to be written by output plugin
			E_TransferSyntax writeXfer;
			wxCSConv*			  m_pConv;
		};
	};
};
