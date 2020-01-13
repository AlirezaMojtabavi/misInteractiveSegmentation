#ifndef misDatasetMacroes_H
#define misDatasetMacroes_h

#include "misGUIElemetStruct.h"
#include "misLogger.h"
#include "misMacros.h"
#include "misPrimaeryNeededHeader.h"
#include "misResultCode.h"
#include "misStrctImageData.h"

//#define  misUpdateListMacro(listName , instanceName) \
//void	Update##listName##NameList() \
//{\
//	this->m_##listName##NameList.clear();\
//	int i;\
//	int imageSeriesNumber;\
//	std::string fullDescription,completeNameList;\
//	char charImageNumber[2];\
//	for (i = 0; i < this->m_##listName##PointerList.size();i++)\
//	{\
//	completeNameList.clear();\
//	imageSeriesNumber = i;\
//	fullDescription = this->m_##listName##PointerList[i]->GetFullDescription();\
//    itoa(imageSeriesNumber,charImageNumber,1);\
//	completeNameList.append(instanceName);\
//	completeNameList.append(" ");\
//    completeNameList.append(charImageNumber);\
//	completeNameList.append(" : ");\
//	completeNameList.append(fullDescription);\
//	this->m_##listName##NameList[i] = completeNameList;\
//	}\
//}

#define  misUpdateListMacro(listName ) \
	void	Update##listName##NameList() \
{\
	this->m_##listName##NameList.clear();\
	int i;\
	int imageSeriesNumber;\
	std::string fullDescription,completeNameList;\
	char charImageNumber[2];\
	for (i = 0; i < this->m_##listName##PointerList.size();i++)\
	{\
	completeNameList.clear();\
	imageSeriesNumber = i;\
	completeNameList = this->m_##listName##PointerList[i]->GetFullName();\
	this->m_##listName##NameList[i] = completeNameList;\
	}\
}

#define  misUpdateDescriptionListMacro(listName ) \
	void	Update##listName##NameList() \
{\
	this->m_##listName##NameList.clear();\
	int i;\
	int imageSeriesNumber;\
	std::string fullDescription,completeNameList;\
	char charImageNumber[2];\
	for (i = 0; i < this->m_##listName##PointerList.size();i++)\
	{\
	completeNameList.clear();\
	imageSeriesNumber = i;\
	completeNameList = this->m_##listName##PointerList[i]->GetFullDescription();\
	this->m_##listName##NameList[i] = completeNameList;\
	}\
}

#define  misGetDataPointerIDMacro(type ) \
	int      Get##listName##DataPointerID(type * pData) \
{\
	int ID;\
	for (ID = 0; i < this->m_##type##PointerList.size();i++)\
	{\
	if (this->m_##type##PointerList[ID] == pData)\
		 {\
		 return ID;\
		 }\
	}\
	ID = -1;\
	return ID;\
}

// TODO:   since only UID could be set only one time it is a error
//         To Do : Add error observer foe else section
//         warning and Error
#define  misDatasetUIDMacro()\
protected:\
	misUID             m_DataObjectUID;\
	int         m_UIDSetOccurance;\
	void SetObjectUID(misUID dataUID)\
	{\
	if(0 == this->m_UIDSetOccurance)\
		{\
		this->m_UIDSetOccurance ++;\
		this->m_DataObjectUID = dataUID;\
		}\
		else\
		{\
		}\
	}\
public:\
	misUID  GetObjectUID() const { return m_DataObjectUID;}

// TODO:   since only UID could be set only one time it is a error
//         To Do : Add error observer foe else section
//         warning and Error
#define  misDatasetUIDMacroPublic()\
private :\
	misUID             m_DataObjectUID;\
	int         m_UIDSetOccurance;\
public:\
	void SetObjectUID(misUID dataUID)\
	{\
	if(0 == this->m_UIDSetOccurance)\
		{\
		this->m_UIDSetOccurance ++;\
		this->m_DataObjectUID = dataUID;\
		}\
		else\
		{\
		}\
	}\
	misUID  GetObjectUID() const { return m_DataObjectUID;}
#define  misSolutionUIDMacro() \
protected: \
	misUID      m_SolutionUID;\
	static int         m_UIDSetOccurance;\
	void SetSolutionUID(misUID dataUID)\
	{\
	if(0 == this->m_UIDSetOccurance)\
		{\
		this->m_UIDSetOccurance ++;\
		this->m_SolutionUID = dataUID;\
		}\
		else\
		{\
		}\
	}\
public:\
	misUID  GetSolutionUID() const { return m_SolutionUID; }

#define  misDatasetInstanceNumberMacro() \
private: \
	int  m_InstanceNumber; \
	void SetInstanceNumber(int instanceNumber) \
	  { \
	  if ( instanceNumber > 0)\
		 {\
		 this->m_InstanceNumber = instanceNumber;\
		 }\
	  }\
public: \
	int  GetInstanceNumber() const { return this->m_InstanceNumber; }

#define  misDataSetNameMacro() \
private: \
	std::string m_FullName;\
	std::string m_FullDescription;\
	std::string m_InstanceName;\
	misResultCode::ResultIds UpdateFullName(void)\
	  {\
	  misResultCode::ResultIds resultID;\
	  if (-1 == this->m_InstanceNumber)\
		 {\
		 this->m_FullName.clear();\
		 resultID = misResultCode::ErUpdateListNameXXXInstanceNumberIsNotUpdated;\
		 std::string errorText = misResultCode::GetStringFromResultCode(resultID);\
		 this->m_FullName.append(errorText);\
		 return resultID;\
		 }\
		 int instanceNo;\
		 char* charImageNumber;\
		 if ( true == this->m_UseInstaceNameForListCreation)\
		 {\
			 this->m_FullName.append(this->m_InstanceName);\
			 this->m_FullName.append(" ");\
		 }\
		 if ( true == this->m_UseInstaceNumberForListCreation)\
		 {\
			 instanceNo = this->m_InstanceNumber;\
			 itoa(instanceNo,charImageNumber,10);\
			 this->m_FullName.append(charImageNumber);\
			 this->m_FullName.append(" : ");\
		}\
		 this->m_FullName.append(this->m_FullDescription);\
		 resultID = misResultCode::NoError;\
		 return resultID;\
	  }\
public:\
	std::string  GetFullDescription() const { return this->m_FullDescription; } \
	std::string  GetFullName() \
	  {\
	  misResultCode::ResultIds result = this->UpdateFullName();\
	  return this->m_FullName;\
	  }

#define misDataSetTransformMacro()\
private:\
	vtkSmartPointer<vtkTransform> m_pTransform;\
public:\
	void setDataSetTransform(vtkTransform * pTransform)\
		{\
		if (this->m_pTransform)\
			{\
			this->m_pTransform->DeepCopy(pTransform);\
			}\
		}\
		vtkSmartPointer<vtkTransform>  GetDataSetTransform(void)\
			{\
			if (this->m_pTransform)\
			return this->m_pTransform;\
			}

#define misTransformMacro()\
private:\
	vtkSmartPointer<vtkTransform> m_pTransform;\
public:\
	void setTransform(vtkTransform * pTransform)\
		{\
		if (this->m_pTransform)\
			{\
			this->m_pTransform->DeepCopy(pTransform);\
			}\
		}\
		vtkSmartPointer<vtkTransform>  GetTransform(void)\
			{\
			if (this->m_pTransform)\
			return this->m_pTransform;\
			}

#define  misInstanceClassMacro() \
	misDatasetUIDMacro\
	misDatasetInstanceNumberMacro();\
	misDataSetNameMacro();\
	misDataSetTransformMacro();\
	misDataSetStateFlageMacro();\
	misCreateVariableWithSetGetMacro(UseInstaceNameForListCreation,bool);\
	misCreateVariableWithSetGetMacro(UseInstaceNumberForListCreation,bool);\
	misCreateVariableWithSetGetMacro(UseFullNameInTheList,bool);

// TO DO : ust be added later

//ZeroMemory(&this->m_DateSetState, sizeof(this->m_DateSetState));\

		  //this->m_InstanceName.append(##instanceName);\
//

#define  misInstanceClassInitialValueMacro(instanceName) \
		  {\
		  this->m_UIDSetOccurance=0;\
		  this->m_InstanceNumber = -1;\
		  this->m_pTransform = itk::SmartPointer<vtkTransform>::New();\
		  this->m_pTransform->Identity();\
		  this->m_InstanceName.append(##instanceName);\
		  this->m_UseInstaceNameForListCreation = true;\
		  this->m_UseInstaceNumberForListCreation = true;\
		  this->m_UseFullNameInTheList = true;\
		  }

#define  misInstanceNumberUnpadeMacro(listName) \
	misResultCode::ResultIds UpdateInstanceNumberof##listName##PionterList()\
	  {\
	  misResultCode::ResultIds resultID;\
	  for (int i = 0; i < this->m_##listName##PointerList.size();i++)\
		 {\
		 try{\
		 this->m_##listName##PointerList[i]->SetInstanceNumber( i+1);\
			 }\
			 catch (int res){\
			 resultID = misResultCode::ErUpdateListNameXXXInstanceNumberIsNotUpdatable;\
			 return resultID;\
						 }\
		 }\
		 resultID = misResultCode::NoError;\
		 return resultID;\
	   }
//
//

/*#define  misDataSetStateFlageMacro()\
	private:\
	misDataSetState   m_DateSetState;\
	private:\
	void SetDataPointerValidity     (bool state) {this->m_DateSetState.DataPointerValid = state;}\
	void SetUIDValidity             (bool state) {this->m_DateSetState.UIDUpdataed = state;}\
	void SetInstanceNumberValidity  (bool state) {this->m_DateSetState.InstanceNumberUpdated = state;}\
	void SetFullNameValidity        (bool state) {this->m_DateSetState.FullNameUpdated = state;}\
	public:\
	void UpdateFinalState ()\
		   {\
		   this->m_DateSetState.AllUpdated = this->m_DateSetState.DataPointerValid \
		   & this->m_DateSetState.UIDUpdataed \
		   & this->m_DateSetState.InstanceNumberUpdated\
		   & this->m_DateSetState.FullNameUpdated;\
		   }\
		   bool GetUIDState           () {return this->m_DateSetState.UIDUpdataed;}\
		   bool GetInstanceNumberState() {return this->m_DateSetState.InstanceNumberUpdated;}\
		   bool GetFullNameState      () {return this->m_DateSetState.FullNameUpdated;}\
		   bool GetDataPointerState   () {return this->m_DateSetState.DataPointerValid;}\
		   bool GetFinalState         () {\
		   this->UpdateFinalState();\
		   return this->m_DateSetState.AllUpdated;\
									  }*/

#define misDatasetNewMacro(x) \
	static Pointer New(void) \
{ \
	this->m_UIDSetOccurance = 1;\
	this->m_DataObjectUID = misIO::GenerateNewUID();\
	Pointer smartPtr; \
	x *rawPtr = new x; \
	smartPtr = rawPtr; \
	rawPtr->UnRegister(); \
	return smartPtr; \
}

#endif