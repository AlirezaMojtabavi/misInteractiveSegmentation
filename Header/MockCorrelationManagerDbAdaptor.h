#include "ICorrelationManagerDbAdaptor.h"
#include "turtle\mock.hpp"

MOCK_BASE_CLASS(MockCorrelationManagerDbAdaptor, ICorrelationManagerDbAdaptor)
{
	MOCK_NON_CONST_METHOD(SaveCorrelationResults, 1, void(std::string solutionUID));
	MOCK_NON_CONST_METHOD(LoadCorrelationResult, 1, void(std::string solutionUID));
	MOCK_NON_CONST_METHOD(SetCorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(SetRepository, 1, void(std::shared_ptr<ICoordinateSystemRepository> val));
};