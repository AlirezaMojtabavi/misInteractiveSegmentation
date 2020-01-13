#include "stdafx.h"
#include "CoordSysCorrelationVariation.h"

#include "ITransformFactory.h"

using namespace parcast;

CoordSysCorrelationVariation::CoordSysCorrelationVariation(
    const std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >& correlMgr,
    const std::shared_ptr<ITransformFactory>& xformFactory)
    : m_CorrelMgr(correlMgr),
    m_XformFactory(xformFactory)
{
}

CoordSysCorrelationVariation::~CoordSysCorrelationVariation() = default;

void CoordSysCorrelationVariation::SetStandardTransform(const std::shared_ptr<ITransform>& xform)
{
    m_StdXform = xform;
}

void CoordSysCorrelationVariation::SetCoordSysIds(const std::string& tool1, const std::string& tool2)
{
    m_Tools[0] = tool1;
    m_Tools[1] = tool2;
}

CoordSysCorrelationVariation::CorrelationStatus CoordSysCorrelationVariation::GetCorrelationStatus() const
{
    if (m_Tools[0] == "" || m_Tools[0] == "" || m_StdXform == nullptr)
    {
        return CorrelationStatus(0, 0, nullptr, false);
    }

    auto correl = m_CorrelMgr->GetTransform(m_Tools[0], m_Tools[1]);
    if (!correl->IsValid())
    {
        return CorrelationStatus(0, 0, nullptr, false);
    }

    auto actualXform = correl->GetTransform();

    auto deviation = actualXform->GetInverse();
    deviation->Concatenate(m_StdXform);
    auto rotationVec = deviation->GetRVec();
    auto translationVec = deviation->GetTVec();

    double actualXformElems[16];
    actualXform->GetMarixElements(actualXformElems);

    return CorrelationStatus(rotationVec.Length(), translationVec.Length(), m_XformFactory->CreateUptr(actualXformElems), true);
}
