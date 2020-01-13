#pragma once

#include "mis3DModelViewingProperties.h"
#include "misColorStruct.h"
#include "misMacros.h"
#include "misStringTools.h"

class misPolyDataPropInImageContainted
{

public:

	misPolyDataPropInImageContainted(void);
	~misPolyDataPropInImageContainted(void);	

 	void SetMaxIndexRepresentObject(int maxIndex);
	int GetMaxIndexRepresentObject() const;
	void SetNumberOfIndexReprsentObject(int index);
	int GetNumberOfIndexReprsentObject() const;
	void SetObjectExtend(int extend[6]);
	bool GetObjectExtend(int* extend);
	void SetObjectTransformMatrix(vtkMatrix4x4* objectTransfromMatrix);
	// Note Take care: it return internal matrix due to the performance considerations !
	vtkMatrix4x4*  GetObjectTransformMatrix(void);
	misColorVector Get2DObjectColormap(void);
	misColorVector Get3DObjectColormap(void);
	int GetStartIndex();
	void SetShowMargin(bool val);
	bool GetShowMargin() const;
	void SetOpacityScale(double opacity_scale);

private:


	misCreateVariableWithSetGetMacro(ParrentImageUID,misUID);
	misCreateVariableWithSetGetMacro(PolyDataUID,misUID);
	misCreateVariableWithSetGetMacro(PolyDataName,std::string);
	misCreateVariableWithSetGetMacro(ObjectVolume,double);
	misCreateVariableWithSetGetMacroWithModificationFlag(PolyDataColor,misColorStruct);
	misCreateVariableWithSetGetMacroWithModificationFlag(ComplementColorForMargin,bool);  // used in 2D
	misCreateVariableWithSetGetMacroWithModificationFlag(OpacityProp,mis3DModelObjectOpacityPropertiesStrct); 
	misCreateVariableWithSetGetMacroWithModificationFlag(AlarmMargin,bool); 
	misCreateVariableWithSetGetMacroWithModificationFlag(MarginValue , double);
	void UpdateColorTransferFunction(void);
	vtkMatrix4x4*  m_ObjectTransform;
	misColorVector m_ObjectColorTF2D; // size is 2^m_NumberOfIndexReprsentObject, it is a map< int, color>  max int is object color, max int-1 object Border
	misColorVector m_ObjectColorTF3D; // size is 2^m_NumberOfIndexReprsentObject, it is a map< int, color>  max int is object color, max int-1 object Border
	int m_ObjectExtend[6];
	int m_MaxIndexRepresentObject;     // between 0 to 15,
	int m_NumberOfIndexReprsentObject;// between 1 to 3, default is 1
	bool m_ModificationFlag;
	bool m_ShowMargin;
	double m_OpacityScale;
};

typedef std::vector<misPolyDataPropInImageContainted> PolyDataSpecificationListTypedef;