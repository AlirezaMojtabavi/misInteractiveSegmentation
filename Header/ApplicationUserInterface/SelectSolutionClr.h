#pragma once

#include "SelectSolution.h"

namespace TmsNavAppCoreClrNS {

	public ref class SelectSolutionClr
	{
	public:
		SelectSolutionClr(std::shared_ptr<parcast::ISelectSolution> selectSolutionNativeCore);

		void CreateNewSolution(
			System::String^ firstName, System::String^ lastName, System::String^ sex, System::DateTime^ birthDate);

	private:
		std::shared_ptr<parcast::ISelectSolution>* m_SelectSolutionNativeCore;
	};

}