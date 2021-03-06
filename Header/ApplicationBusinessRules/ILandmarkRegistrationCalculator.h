#pragma once
#include "IViewingTypeColormapSelector.h"
#include "misRegistrationStrcts.h"
#include "mislandMarkPosAndStatusStr.h"
#include "misPairLandmarkStr.h"

struct RegistrationResultStr;

class ILandmarkRegistrationCalculator
{
public:
	virtual ~ILandmarkRegistrationCalculator() = default;
	virtual void GetRegistrationMatrix(double transMat[16]) const = 0;
	virtual RegistrationResultStr GetRegistrationResult() const = 0;
	virtual int GetNumberOfFixedLandmarks() const = 0;
	virtual int GetNumberOfValidFixedLandmarks() = 0;
	virtual int GetMinimumPointForRegistration() = 0;
	virtual misPairLandMarkStatusListType GetPairLandMarkStatusList() = 0;
	virtual void AddFixedLandMark(int index, misItkPointType newPointInImage) = 0;
	virtual void AddFixedLandMark(int index, double newPointInImage[3]) = 0;
	virtual void AddMovableLandmark(int index, double capturedPosition[3]) = 0;
	virtual std::shared_ptr<misPairLandMarkListType> GetAllLandmarks() const = 0;
	virtual misPairLandMarkStr GetPairLandmark(int index) = 0;
	virtual int GetLandmarksNumber() = 0;
	virtual bool GetFinalRegistationLists(misItkListPointType* pFixedPintList, misItkListPointType* pCapturedPointList) = 0;
	virtual bool DeleteLandmarkFixed(int index) = 0;
	virtual bool DeleteLandmarkMovable(int index) = 0;
	virtual std::vector<mislandMarkPosAndStatusStr> GetFixedLandmarkDataList() = 0;
	virtual std::vector<mislandMarkPosAndStatusStr> GetMovableLandmarkDataList() = 0;
	virtual TREStrct GetDistanseToNearestFixedPoint(misItkPointType newPosition) = 0;
	virtual double* GetFixedPositionValue(int index) = 0;
	virtual double* GetMovalePositionValue(int index) = 0;
	virtual double* GetRegisterdPointValue(int index) = 0;
	virtual void ResetRegistrationTransform() = 0;
	virtual void UpdateCapturedPointStatus() = 0;
	virtual void AddMovableLandmark(int index, misItkPointType capturedPosition) = 0;
	virtual void AddEmptyLandmark() = 0;
	virtual void SetMinimumPointForRegistration(int number) = 0;
	virtual void DeleteAll() = 0;
	virtual void DeleteAllMovableLandmark() = 0;
	virtual void ClearPairLandmark(int index) = 0;
	virtual void DeletePairLandmark(int index) = 0;
	virtual void DeleteInvalidLandmarks() = 0;
	virtual void SetRegistrationTransform(vtkMatrix4x4* pRegistrationTrnasform) = 0;
};