#ifndef __igstkBiopsyPolarisTrackerTool_h
#define __igstkBiopsyPolarisTrackerTool_h

#include "igstkTrackerTool.h"

namespace igstk
{
	class BiopsyPolarisTrackerTool : public TrackerTool
	{
	public:
		igstkStandardClassTraitsMacro(BiopsyPolarisTrackerTool, TrackerTool)

	protected:

		BiopsyPolarisTrackerTool();
		virtual void PrintSelf(std::ostream& os, ::itk::Indent indent) const;

	private:

		void operator=(const Self&);
		bool CheckIfTrackerToolIsConfigured() const override;
		//purposely not implemented
	};

}

#endif  // __igstk_BiopsyPolarisTrackerTool_h_
