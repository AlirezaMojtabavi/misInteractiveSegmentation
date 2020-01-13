#pragma once

#include "ICoordSysCorrelationVariationAdapterUi.h"

namespace parcast
{

    class CoordSysCorrelationVariationAdapterUi : public ICoordSysCorrelationVariationAdapterUi
    {
    public:
        CoordSysCorrelationVariationAdapterUi(itk::Object::Pointer parent, const std::string& sequenceName,
                                              const std::string& subSequenceName);

		template <class EventType, typename PayloadType>
		void InvokeParentLoadedEvent(const PayloadType& payload)
		{
			EventType ev;
			ev.Set(payload);
			ev.SetSequenceName(m_SequenceName);
			ev.SetSubTab(m_SubsequenceName);
			m_ParentEventHandler->InvokeEvent(ev);
		}

        void UpdateTools(const std::string& tool1, const std::string& tool2);
        void UpdateAngularDeviation(const std::string& angleDegrees);
        void UpdateRadialDeviation(const std::string& distanceMm);

    private:
        itk::Object::Pointer m_ParentEventHandler;
		const std::string m_SequenceName;
		const std::string m_SubsequenceName;
    };

}
