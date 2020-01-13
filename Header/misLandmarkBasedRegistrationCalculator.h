#pragma once

#include "misGuiStructures.h"
#include "misMacros.h"
#include "misRegistrationEnums.h"
#include "misitkTypdef.h"
#include "ApplicationBusinessRules/ILandmarkRegistrationCalculator.h"
#include "mislandMarkPosAndStatusStr.h"
#include "misRegistrationStrcts.h"

struct misPairLandMarkStr;
struct misPairLandMarkStatusStr;

typedef std::vector<misPairLandMarkStatusStr> misPairLandMarkStatusListType;
typedef std::vector<misPairLandMarkStr> misPairLandMarkListType;

//calculate matrix transform between 2  set of point cloud,at least 3 point for each set is needed
class  misLandmarkBasedRegistrationCalculator : public ILandmarkRegistrationCalculator
{

public:
	misLandmarkBasedRegistrationCalculator(int minimumPointForRegistration, int initialNumberOfPointsForRegistration,
		misLandmarkBasedRegistrationCalculationType landomarkType);

 	misPairLandMarkStatusListType GetPairLandMarkStatusList() override;
	RegistrationResultStr GetRegistrationResult() const override;
	virtual void AddFixedLandMark(int index, misItkPointType newPointInImage) override;
	virtual void AddFixedLandMark(int index, double newPointInImage[3])override;
	virtual void AddMovableLandmark(int index, double capturedPosition[3])override;
	std::shared_ptr<misPairLandMarkListType> GetAllLandmarks() const override;
	misPairLandMarkStr GetPairLandmark(int index) override;
	int GetLandmarksNumber() override;
	int GetNumberOfFixedLandmarks() const override;
	int GetNumberOfValidFixedLandmarks() override;
	bool GetFinalRegistationLists(misItkListPointType* pFixedPintList, misItkListPointType* pCapturedPointList) override;
	bool DeleteLandmarkFixed(int index) override;
	bool DeleteLandmarkMovable(int index) override;
	std::vector<mislandMarkPosAndStatusStr> GetFixedLandmarkDataList() override;
	std::vector<mislandMarkPosAndStatusStr> GetMovableLandmarkDataList() override;
	TREStrct GetDistanseToNearestFixedPoint(misItkPointType newPosition) override;
	double* GetFixedPositionValue(int index) override;
	double* GetMovalePositionValue(int index) override;
	double* GetRegisterdPointValue(int index) override;
	void ResetRegistrationTransform()override;
	void UpdateCapturedPointStatus()override;
	void AddMovableLandmark(int index, misItkPointType capturedPosition)override;
	void AddEmptyLandmark()override;
	void SetMinimumPointForRegistration(int number)override;
	void DeleteAll()override;
	void DeleteAllMovableLandmark()override;
	void GetRegistrationMatrix(double transMat[16]) const override;
	void ClearPairLandmark(int index)override;
	void DeletePairLandmark(int index)override;
	void DeleteInvalidLandmarks()override;
	void SetRegistrationTransform(vtkMatrix4x4* pRegistrationTrnasform)override;
	int GetMinimumPointForRegistration() override;
protected:
	int m_MinimumPointForRegistration;
	int m_InitialNumberOfPointsForRegistration;
	void UpdateRegistrationError();
	void AddNewPairLandMark(double newPointInImage[3]);
	void UpdateRegistrationTransform();
	void UpdateFinalValidList(std::vector<mislandMarkPosAndStatusStr>& listFixedLandmarks, std::vector<mislandMarkPosAndStatusStr>& listMovableLandmarks);


protected:
	RegistrationResultStr m_RegistrationResult;
	std::shared_ptr<misPairLandMarkListType> m_LandMarkList = std::make_shared<misPairLandMarkListType>();
	vtkSmartPointer<vtkMatrix4x4> m_RegistrationTransform;
	vtkSmartPointer<vtkMatrix4x4> m_InitialRegisterationMatrix;
	bool m_IsInitialRegistrationMatrixUsed;
	bool m_IsValidRegistrationTransform;
	misLandmarkBasedRegistrationCalculationType  m_LandmarkType;
	int m_minRequiredPtsForPointBasedRegistration;
};