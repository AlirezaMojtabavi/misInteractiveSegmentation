// TmsNavAppCoreClr.h
#pragma once

#include "SelectSolutionClr.h"
#include "TmsNavAppCore.h"

namespace TmsNavAppCoreClrNS {

	public ref class TmsNavAppCoreClr
	{
	public:
		TmsNavAppCoreClr(std::shared_ptr<parcast::TmsNavAppCore> nativeAppCore);
		~TmsNavAppCoreClr();

		SelectSolutionClr^ GetSelectSolution();
		
		void UpdateStatus();

	private:
		std::shared_ptr<parcast::TmsNavAppCore>* m_NativeAppCore;
		// TODO: Add your methods for this class here.
	};

}
