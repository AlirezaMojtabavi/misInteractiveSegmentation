#include <turtle/mock.hpp>

#include "ICoordinateSystemRepository.h"


MOCK_BASE_CLASS(MockCoordinateSystemRepository, ICoordinateSystemRepository)
{
	MOCK_NON_CONST_METHOD(AddCoordinateSystem, 1, void (std::shared_ptr<ICoordinateSystem> coordinatesSystem));
	MOCK_NON_CONST_METHOD(RemoveCoordinateSystem, 1, void (std::shared_ptr<ICoordinateSystem> coordinatesSystem));
	MOCK_NON_CONST_METHOD(AppendSubscriberToAddCoordinateSystem, 1, void (std::function<SubscriberType> subscriber));
	MOCK_NON_CONST_METHOD(AppendSubscriberToRemovingCoordinate, 1, void (std::function<SubscriberType> subscriber));
	MOCK_CONST_METHOD(GetCoordinateSystem, 1, std::shared_ptr<ICoordinateSystem> (misUID coordinateSystemUID));
	MOCK_CONST_METHOD(GetAllCoordinatesSystems, 0, std::vector<std::shared_ptr<ICoordinateSystem>> ());
};