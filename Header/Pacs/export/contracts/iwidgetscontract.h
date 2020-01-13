#pragma once
/*
*
*  $Id: iwidgetscontract.h $
*  Ginkgo CADx Project
*
*  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
*  http://ginkgo-cadx.com
*
*  This file is licensed under LGPL v3 license.
*  See License.txt for details
*
*/
#ifndef IWIDGETSCONTRACT_H
#define IWIDGETSCONTRACT_H

#include <list>

#include <api/api.h>
#include <api/icontract.h>

class vtkGinkgoImageViewer;

namespace GNC {
	namespace GCS {
		class IVista;
		class IWidgetsManager;
	}
}

namespace GNC {
	namespace GCS {

		class EXTAPI IWidgetsContract : public IContract {
		public:

			typedef std::list<vtkGinkgoImageViewer*> TViewerList;

			IWidgetsContract();

			~IWidgetsContract();

			virtual GNC::GCS::IWidgetsManager* GetManager() = 0;

			virtual void GetAllViewers(TViewerList& viewerList);

			bool Inicializado();

			virtual vtkGinkgoImageViewer* GetViewerActivo() = 0;
		};
	}
}
#endif