#pragma once


MOCK_BASE_CLASS(MockCompeleteImageDependencies, ICompeleteImageDependencies)
{
	MOCK_CONST_METHOD(GetImage, 0, std::shared_ptr<IImage>());
	MOCK_NON_CONST_METHOD(SetImage, 1, void (std::shared_ptr<IImage>));
	MOCK_CONST_METHOD(GetName, 0, std::string ());
	MOCK_NON_CONST_METHOD(SetName, 1, void (std::string));
	MOCK_CONST_METHOD(GetOpacity, 0, double());
	MOCK_NON_CONST_METHOD(SetOpacity, 1, void (double));
	MOCK_CONST_METHOD(GetObjectUID, 0, misUID());
	MOCK_NON_CONST_METHOD(SetObjectUID, 1, void(misUID));
	MOCK_CONST_METHOD(GetVisibility, 0, bool());
	MOCK_NON_CONST_METHOD(SetVisibility, 1, void (bool));
};

