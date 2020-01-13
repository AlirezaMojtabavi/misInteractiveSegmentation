#ifndef MISPOLYDATA_H_HEADER_INCLUDED_B7EA294D
#define MISPOLYDATA_H_HEADER_INCLUDED_B7EA294D

#include "misDatasetMacroes.h"
#include "misEnums.h"
#include "misMacros.h"
#include "misStrctImageData.h"
#include "misobjectProperitiesEnums.h"
#include "misColorStruct.h"
#include "misVolumeViewingTypes.h"

class misDataSetsUtility;

//#include "misDataSetsUtility.h"


//##ModelId=4815A5A80213
class  misPolyData : public vtkPolyData
{
	friend class misDataBaseIO;

public:
	friend class misDataBaseIO;

	misDatasetUIDMacro();
	misCreateVariableWithProtectedSetGetMacro(ModificationFlag, bool);
	misCreateVariableWithProtectedSetGetMacro(ModificationFlagBinariesPart, bool);
	misCreateVariableWithSetGetMacroWithModificationFlag(Name, std::string);
	misCreateVariableWithSetGetMacroWithModificationFlag(BinaryFileName, std::string);
	misCreateVariableWithSetGetMacroWithModificationFlag(ParentImageUID, misUID);
	misCreateVariableWithSetGetMacroWithModificationFlag(Color, misColorStruct);
	misCreateVariableWithSetGetMacroWithModificationFlag(PolydataType, mis3DModelTypes);
	misCreateVariableWithSetGetMacroWithModificationFlag(RenderingType, mis3DModelRenderingType);
	misCreateVariableWithSetGetMacroWithModificationFlag(volume, double);

	static misPolyData* New()
	{
		return new misPolyData;
	};

	virtual void DeepCopy(vtkDataObject *src);
	MisObjectType GetObjectType()
	{
		return this->m_ObjectType;
	}

protected:
	misPolyData();
	~misPolyData();

	void CallModificationObserver() {};

private:
	MisObjectType  m_ObjectType;

};

#endif /* MISPOLYDATA_H_HEADER_INCLUDED_B7EA294D */
