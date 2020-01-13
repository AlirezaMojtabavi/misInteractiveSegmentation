#pragma once
/*
 *  
 *  $Id: iviewcontractable.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 */

#include <api/icontract.h>

namespace GNC {
	namespace GCS {
		class IImageExportContract;
		class EXTAPI IImageExportContractable: public GNC::GCS::IContractable
		{
		public:
			IImageExportContractable();
			virtual ~IImageExportContractable();

			virtual bool IsValidContract(IContract* contract);

			
			virtual void Register(IContract* contract);
		protected:
			GNC::GCS::IImageExportContract* ExportContract;
		};
	}
}
