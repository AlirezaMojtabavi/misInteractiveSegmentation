/*
 *  
 *  $Id: icontroladorinternacionalizacion.h $
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
#include <string>
namespace GNC {
	namespace GCS {
		class IControladorInternacionalizacion {
		public:			
			IControladorInternacionalizacion() { }
			virtual ~IControladorInternacionalizacion() { }
			
			virtual void AddCatalog(const std::string& catalogName) = 0;
		};
	}
}
