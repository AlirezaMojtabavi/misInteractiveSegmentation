#pragma once

#include "IImageToPatientLandmarkBasedRegistation.h"

MOCK_BASE_CLASS(MockImageToPatientLandmarkBasedRegistation, IImageToPatientLandmarkBasedRegistation)
{
	MOCK_NON_CONST_METHOD(GetPairLandMarkStatusList, 0, misPairLandMarkStatusListType());
	MOCK_CONST_METHOD(GetRegistrationResult, 0, RegistrationResultStr());
	MOCK_NON_CONST_METHOD(AddFixedLandMark, 2, void(int index, misItkPointType newPointInImage), AddFixedLandMark_1);
	MOCK_NON_CONST_METHOD(AddFixedLandMark, 2, void(int index, double newPointInImage[3]), AddFixedLandMark_2);
	MOCK_NON_CONST_METHOD(AddFixedLandMark, 3, void(int index, misItkPointType newPointInImage, misLandmarkType	landmarkType ), AddFixedLandMark_3);
	MOCK_NON_CONST_METHOD(AddFixedLandMark, 3, void(int index, double newPointInImage[3], misLandmarkType landmarkType ), AddFixedLandMark_4);
	MOCK_NON_CONST_METHOD(AddMovableLandmark, 2, void(int index, double capturedPosition[3]), AddMovableLandmark_1);
	MOCK_NON_CONST_METHOD(AddMovableLandmark, 2, void(int index, misItkPointType capturedPosition), AddMovableLandmark_2);
	MOCK_NON_CONST_METHOD(GetAllLandmarks, 0, std::shared_ptr<misPairLandMarkListType>());
	MOCK_NON_CONST_METHOD(GetPairLandmark, 1, misPairLandMarkStr(int index));
	MOCK_NON_CONST_METHOD(GetLandmarksNumber, 0, int());
	MOCK_CONST_METHOD(GetNumberOfFixedLandmarks, 0, int());
	MOCK_NON_CONST_METHOD(GetNumberOfValidFixedLandmarks, 0, int());
	MOCK_NON_CONST_METHOD(GetFinalRegistationLists, 2, bool(misItkListPointType* pFixedPintList, misItkListPointType* pCapturedPointList));
	MOCK_NON_CONST_METHOD(DeleteLandmarkFixed, 1, bool(int index));
	MOCK_NON_CONST_METHOD(DeleteLandmarkMovable, 1, bool(int index));
	MOCK_NON_CONST_METHOD(GetFixedLandmarkDataList, 0, std::vector<mislandMarkPosAndStatusStr>());
	MOCK_NON_CONST_METHOD(GetMovableLandmarkDataList, 0, std::vector<mislandMarkPosAndStatusStr>());
	MOCK_NON_CONST_METHOD(GetDistanseToNearestFixedPoint, 1, TREStrct(misItkPointType newPosition));
	MOCK_NON_CONST_METHOD(GetFixedPositionValue, 1, double*(int index));
	MOCK_NON_CONST_METHOD(GetMovalePositionValue, 1, double*(int index));
	MOCK_NON_CONST_METHOD(GetRegisterdPointValue, 1, double*(int index));
	MOCK_NON_CONST_METHOD(ResetRegistrationTransform, 0, void());
	MOCK_NON_CONST_METHOD(UpdateCapturedPointStatus, 0, void());
	MOCK_NON_CONST_METHOD(AddEmptyLandmark, 0, void());
	MOCK_NON_CONST_METHOD(SetMinimumPointForRegistration, 1, void(int number));
	MOCK_NON_CONST_METHOD(DeleteAll, 0, void());
	MOCK_NON_CONST_METHOD(DeleteAllMovableLandmark, 0, void());
	MOCK_CONST_METHOD(GetRegistrationMatrix, 1, void(double transMat[16]));
	MOCK_NON_CONST_METHOD(ClearPairLandmark, 1, void(int index));
	MOCK_NON_CONST_METHOD(DeletePairLandmark, 1, void(int index));
	MOCK_NON_CONST_METHOD(DeleteInvalidLandmarks, 0, void());
	MOCK_NON_CONST_METHOD(SetRegistrationTransform, 1, void(vtkMatrix4x4* pRegistrationTrnasform));
	MOCK_NON_CONST_METHOD(UpdateSettingFromAppSetting, 0, void());
	MOCK_NON_CONST_METHOD(AllLandmarksCaptured, 0, bool());
	MOCK_NON_CONST_METHOD(AttemptToCapture, 1, bool(int index));
	MOCK_CONST_METHOD(GetImagelandmarkType, 1, misLandmarkType(int index));
	MOCK_CONST_METHOD(GetCorrespondingLandmarkVolumeType, 2, misVolumeViewingTypes(int index, misApplicationType appType));
	MOCK_NON_CONST_METHOD(GetMinimumPointForRegistration, 0, int () );
	MOCK_NON_CONST_METHOD( GetClaculator, 0, std::shared_ptr<ILandmarkRegistrationCalculator> () );
};
