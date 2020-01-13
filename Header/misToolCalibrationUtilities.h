#pragma once
//#include "misToolAccuracy.h"
#include "misLogger.h"
#include <vector>
#include "TipCalibrationWithSVDresults.h"
#include "xmlserializer.h"
#include "xmldeserializer.h"

using namespace igstk;

//This class was written by -M.A- for handling tool calibration based on 3 approaches
//1- Pivot Calibration with Precalculated Pivot,
//2- Pivot Calibration with Pivot recalculating,
//3- and single point

class misToolCalibrationUtilities 
{
public:
	friend class misToolAccuracySubSequence;

	typedef ::itk::Vector<double, 3>    VectorType;
	typedef igstk::Transform           TransformType;
	typedef std::vector<TransformType> TransformContainerType;


	misToolCalibrationUtilities(void);
	~misToolCalibrationUtilities(void);

	//Don`t checks if the DataPoint is a valid data.
	//inserts tool and reference transforms into a container which stores 
	//data points used in calibration process
	//@param ToolDataPoint, input, the transform of tool
	//@param RefPoint, input, the transform of reference
	void InsertDataIntoContainer(TransformType * ToolDataPoint,TransformType * RefPoint);

	//Resets the tool and reference gathered data
	void ResetContainer();

	//Returns the gathered transforms of tool
	TransformContainerType * GetToolDataPoints();//TODO: -M.A- make the return type const

	//Returns the gathered transforms of reference
	TransformContainerType * GetReferencePoints();//TODO: -M.A- make the return type const

	//Calculates maximum error of the data points
	//NOTICE: This function works only when we calculate pivot and offset. Hence we don`t use 
	//this function when we do our calculations with 3 points to find just offset.
	//@param OffsetsAndPivot, input, Calculated offset and pivots. This means ??????????????
	//Output, Resulting maximum error of data points
	double ComputeMaxError( vnl_vector<double> OffsetsAndPivot);

	//Calculates mean error of the data points
	//NOTICE: This function works only when we calculate pivot and offset. Hence we don`t use 
	//this function when we do our calculations with 3 points to find just offset.
	//@param OffsetsAndPivot, input, Calculated offset and pivots.
	//Output, Resulting mean error of data points
	double ComputeMeanError(vnl_vector<double> OffsetsAndPivot);

	//Calculates Root Mean Square error of the data points
	//We try to solve Ax=b here
	//@param A, input, consists of [Rotation, -I]
	//@param b, input, consists of (-1) * translations of tool
	//@param x, input, consists of offset (x[0] ~ x[2]) and pivot (x[3] ~ x[5])
	//output double, rmse
	double ComputeRMSE(vnl_matrix< double > A, vnl_vector< double > b, vnl_vector< double > x);

	//Sets the number of data points used in data gathering phase
	//and also checks the boundaries of data (up and down)
	void SetNumberOfDataPoints(int num);

	//Gets the number of data points used in data gathering phase
	int GetNumberOfDataPoints();

	////Serialization utility
	//virtual void serialize(XmlSerializer& s);

	////Deserialization utility
	//virtual void deserialize(XmlDeserializer& s);

	//Sets Maximum threshold of data gathering process
	void SetMaxAcceptableNumberOfData(int MaxAcceptable);

	//Sets Minimum threshold of data gathering process
	void SetMinAcceptableNumberOfData(int MinAcceptable);

	//Gets Maximum threshold of data gathering process
	int GetMaxAcceptableNumberOfData();

	//Gets Minimum threshold of data gathering process
	int GetMinAcceptableNumberOfData();

	//Approximates quality of NDI spheres of m_subject tool 
	//@param RMSE, input, calculated RMSE in pivot calibration.
	//@param MaxError, input, calculated MaxError in pivot calibration
	//@param SVDmax, input, calculated maximum Eigen value in SVD approach
	//@param SVDmin, input, calculated minimum Eigen value in SVD approach
	double ApproximateNDISpheresQuality(double RMSE, double MaxError,double SVDmax,double SVDmin);//Added by -M.A-

private:

	misLogger * m_Logger;

	//Number of data points that are gathered during pivot calibration
	int m_NumberOfDataPointsNeeded;
	
	//A vector containing tool transformations (See comments of GatheredReferencePoints)
	TransformContainerType * m_GatheredToolPoints;

	//A vector containing Reference transformations. The vector size of GatheredToolPoints and 
	//GatheredReferencePoints are the same and for element i in this vector, the GatheredReferencePoints[i]
	//represents the reference transform with respect to GatheredToolPoints[i]. This means when gathering GatheredToolPoints[i]
	//transformation, The GatheredReferencePoints[i] represents the reference transform respectively
	TransformContainerType * m_GatheredReferencePoints;

	//A threshold for SVD process which its initial value(0.1) is based on an igstk test
	double m_SingularValueDecmpositionThreshold;

	//
	int m_MaxAcceptableNumberOfDataPoints;
	int m_MinAcceptableNumberOfDataPoints;

protected:
	
	//Calculates Pivot and offset of tool simultaneously without considering reference point
	//@param ResultOffset: output, is the calculated offset
	//@param ResultPivot: output, is the calculated pivot
	//@param RMSE: output, is the Root mean square of errors
	//@param ResultMaxPointError: output, is the max error of data
	void ComputeCalibrationWithMoreThanOneValueWith6PointsAndCalculatePivot(double ResultOffset [],double ResultPivot [], double * RMSE, double * ResultMaxPointError);
	
	//NOTICE: TO SEE THE LOGIC OF THIS FUNCTION WHICH IS A CENTERIC LOGIC GO TO:
	//\\misserver90\Team Folders\M.Amiri\Documents for calibration\Logics\misToolCalibrationUtilities--ComputeCalibrationWith6PointsWithRefConsideration.docx
	//Calculates Pivot and offset of tool with considering reference current position. This means we
	//try to tolerate reference movement during data gathering in pivot calibration
	//@param Results: output, is the calculated offset, pivot and errors
	//if the result returned contain all members equal to -1, an error occured during data gathering process
	SVDTipCalibrationResults TipCalibrationWithSVD();
	

	////checks whether the pivot point was fixed on the sharp point of reference during data gathering
	//bool CheckPivotPointWasFixedDuringDataGatheringProcess(double AcceptableError);
	
	
	////Calculates Pivot and offset of tool without considering the reference current position.
	////We consider the precalculated pivot and then calculate the offset based on this point
	////@param ReferenceCalibrationPoint, input, The precalculated pivot point
	////@param ResultOffset: output, is the calculated offset
	////@param RMSE: output, is the Root mean square of errors
	//void ComputeCalibrationWithMoreThanOneValueWith3PointsConsideringPrecalculatedPivot( double ReferenceCalibrationPoint[],double ResultOffset [], double * RMSE );



	
};

