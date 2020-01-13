/*
 *  
 *  $Id: icontroladorcarga.h $
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
#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <api/icommand.h>
#include <api/ilock.h>
#include <api/controllers/proxies/ipipelineproperties.h>

#ifdef __DEPRECATED
#undef __DEPRECATED
#endif
#include <vtkSmartPointer.h>
#include <api/autoptr.h>
namespace GIL {
	class IModeloIntegracion;
}

namespace GNC {
	namespace GCS {
		class IVista;
	}
}
class vtkImageData;
class vtkAlgorithmOutput;

namespace GNC {
	namespace GCS {

		class ControladorCargaException : public GNC::GCS::IException {
		public:
			ControladorCargaException(const std::string& msg, const std::string& componente="Modelo", bool fatal = true);
			
			~ControladorCargaException() throw();
		protected:
		};

		class IStreamingLoader;
		class IControladorCarga {
		public:
			typedef std::list<std::string> ListaRutas;
			typedef std::list<ListaRutas> TListaDeListaDeRutas;
			
			virtual vtkSmartPointer<vtkImageData> CargarITKMultidimensional(IComando* cmd, ListaRutas& listaFicheros, int* orientacion, double* spacing = NULL) = 0;
			virtual vtkSmartPointer<vtkImageData> CargarITK(IComando* cmd, std::string& path, int* orientacion, double* spacing = NULL) = 0;
			
			virtual void CargaAsincrona(GNC::GCS::IVista* pVista, const bool loadFirst = true) = 0;

			//region Creacion y destruccion de componente de carga en streaming
			virtual IStreamingLoader* NewLoader() = 0;
			virtual void FreeLoader(GNC::GCS::IStreamingLoader** loader) = 0;
			//endregion

		protected:
			IControladorCarga();
			~IControladorCarga();
		};

		
		class EXTAPI IStreamingLoader : public IPipelineProperties, public GNC::GCS::ILockable {
		public:
			//region Constructor
			IStreamingLoader();

			virtual ~IStreamingLoader();

			virtual bool IsSignalFile() = 0;

			/** Fija un fichero de entrada y reestablece el pipeline interno de carga si es necesario **/
			virtual void SetInput(const std::string& fichero) = 0;

			/** Devuelve el puerto de salida **/
			virtual vtkSmartPointer<vtkAlgorithmOutput> GetOutputPort() = 0;

			/** Devuelve por parametro una copia de la imagen **/
			virtual void GetOutputCopy(vtkSmartPointer<vtkImageData>& output) = 0;

			/** establece el spacing **/
			virtual void SetOutputSpacing(double spacing[3]) = 0;

			/** establece el origen **/
			virtual void SetOutputOrigin(double origin[3]) = 0;

			/** **/
			virtual std::string  GetPatientPosition()  = 0;
			
		};
	}
}
