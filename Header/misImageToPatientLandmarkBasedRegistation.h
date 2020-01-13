#pragma once
#include "misLandmarkBasedRegistrationCalculator.h"
#include "IImageToPatientLandmarkBasedRegistation.h"

class  misImageToPatientLandmarkBasedRegistation : public IImageToPatientLandmarkBasedRegistation
{
public:
	misImageToPatientLandmarkBasedRegistation(int minimumPointForRegistration, int initialNumberOfPointsForRegistration,
		misLandmarkBasedRegistrationCalculationType landmarkType);
 	bool AllLandmarksCaptured();
	bool AttemptToCapture(int index);
	virtual void AddFixedLandMark(int index, misItkPointType  newPointInImage,misLandmarkType landmarkType = UnkownLandmarkType);
	virtual void AddFixedLandMark(int index, double  newPointInImage[3],misLandmarkType landmarkType = UnkownLandmarkType);
	void AddFixedLandMark(int index, misItkPointType newPointInImage) override;
	void AddFixedLandMark(int index, double newPointInImage[3]) override;

	misLandmarkType GetImagelandmarkType(int index) const;
	misVolumeViewingTypes GetCorrespondingLandmarkVolumeType( int index , misApplicationType appType) const;
	int GetMinimumPointForRegistration() override;
	std::shared_ptr<ILandmarkRegistrationCalculator> GetClaculator() override;
	misPairLandMarkStatusListType GetPairLandMarkStatusList() override;
	RegistrationResultStr GetRegistrationResult() const override;
	void AddMovableLandmark(int index, double capturedPosition[3]) override;
	std::shared_ptr<misPairLandMarkListType>  GetAllLandmarks() override;
	misPairLandMarkStr  GetPairLandmark(int index) override;
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
	void ResetRegistrationTransform() override;
	void UpdateCapturedPointStatus() override;
	void AddMovableLandmark(int index, misItkPointType capturedPosition) override;
	void AddEmptyLandmark() override;
	void SetMinimumPointForRegistration(int number) override;
	void DeleteAll() override;
	void DeleteAllMovableLandmark() override;
	void GetRegistrationMatrix(double transMat[16]) const override;
	void ClearPairLandmark(int index) override;
	void DeletePairLandmark(int index) override;
	void DeleteInvalidLandmarks() override;
	void SetRegistrationTransform(vtkMatrix4x4* pRegistrationTrnasform) override;
private:
	std::shared_ptr<misLandmarkBasedRegistrationCalculator> m_Calculator;
};
