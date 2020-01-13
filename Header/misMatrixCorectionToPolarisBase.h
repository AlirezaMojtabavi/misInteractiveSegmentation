#pragma once

#include "misTrackingManagerEnums.h"

class misMatrixCorectionToPolarisBase
{
public:
	misMatrixCorectionToPolarisBase(vtkMatrix4x4 * CurrentCorrectionMatrix);
	~misMatrixCorectionToPolarisBase(void);
	//returns camera2openGl corrector matrix
	vtkMatrix4x4 * GetOpenGlCorrectorMatrix();
	void InitializeCorrectorMatrices();

	//changes the raw transform into a standard transform so that you can use them in a unique manner. This
	//process makes you sure that third column of tool transform matrix is direction of shaft and so on... 
	//This method changes tool transform matrix into a matrix with a predefined standard. For more detail refer to
	//document 'Tool and Tracker and OpenGL Corrector matrices in misProject.docx' in TeamFolder folder in address: 
	//'\\MISSERVER90\Team Folders\M.Amiri\CORRECTOR MATRIXES IN misProject'
	vtkMatrix4x4*  ChangeRawToolTransformIntoReferenceTransform(igstk::Transform inputRawTransforn);
	vtkMatrix4x4* UpdateRawToolTransform(igstk::Transform rawTransfrom,double* tipOffset);
	
private:
	TrackerType				m_TrackerType;
	//A corrector matrix to change local coordinate of tracker into global coordinate of OpenGL.
	//This matrix initializes based on type of tracker
	vtkMatrix4x4 * m_CameraCorrectionMatrix2OpenGl;

	//A corrector to unifying STL representation for all tracker types
	//This matrix is set based on tracker. Its duty is to change coordinate of 
	//Micron and Ascension into STL of Polaris. See STL coordinate of Polaris and
	//STL coordinate of Micron. Then you can find this corrector which is multiplied to 
	//STL coordinate of Micron and after that changes it into coordinate of Polaris. This
	//corrector matrix is just used in visualization aspect of application. See 
	//misToolData::UpdateRepresentatorUserTransforms() to find out how this matrix is 
	//used. Notice that the order of this multiplication is very important. Apart from other 
	//places in the project we must multiply in this form: TansformOfTool x STLCorrector. 
	//vtkMatrix4x4 * m_STLCorrectionMatrix;


	//This matrix corrects only translation part of raw transform into Standard format
	//and also changes specific tool transform into standard tool transform  (POLARIS TOOL)
	vtkMatrix4x4 * m_SpecificToolToStandardToolCorrectorMatrix;

	//This is the invert of matrix m_SpecificToolToStandardToolCorrectorMatrix. We have set this matrix 
	//as a class member to have a better performance and not to call new and delete in a recursive manner
	vtkMatrix4x4 * m_INVERTSpecificToolToStandardToolCorrectorMatrix;

	//This matrix corrects only rotation part of the raw transform into Standard format
	//and also changes specific tracker coordinates into standard tracker coordinates (POLARIS TRACKER)
	vtkMatrix4x4 * m_SpecificTRACKERtoStandardTRACKERCorrectorMatrix;

	//This is the invert of matrix m_SpecificTRACKERtoStandardTRACKERCorrectorMatrix. We have set this matrix 
	//as a class member to have a better performance and not to call new and delete in a recursive manner
	vtkMatrix4x4 * m_INVERTSpecificTRACKERtoStandardTRACKERCorrectorMatrix;
};

