#pragma once
//#ifndef __MISADDTRACKERTOOLRW__
//#define __MISADDTRACKERTOOLRW__
//#ifndef MISCOMPORTSETTINGRW_H_HEADER_INCLUDED
//#define MISCOMPORTSETTINGRW_H_HEADER_INCLUDED

#ifndef MISXMLIO_H_HEADER_INCLUDED
#define MISXMLIO_H_HEADER_INCLUDED

#include <string>
#include "misStrctToolData.h"
#include "misTrackingManagerTypes.h"
#include "misApplicationSetting.h"
#include "misEventFromGui.h"

using namespace System;
using namespace System::IO;
using namespace System::Xml;
//---------------------------------------------------------------
//ref class misAddTrackerToolRW
#pragma make_public(char) 

public ref class misXMLIO
{
private:
	   misApplicationSetting* m_AppSetting;
	   
	   void readToolCategory(XmlDocument^ Document, misStrctToolData* tool);
	   void readToolName(XmlDocument^ Document, misStrctToolData* tool);
	   void readToolDeletionStatus(XmlDocument^ Document, misStrctToolData* tool);
	   void IsRegisterationTool(XmlDocument^ Document, misStrctToolData* tool);
	   void ReadCalibrationToolData(XmlDocument^ Document, misStrctToolData* tool);
	   void ReadReferenceInfo(XmlDocument^ Document, misStrctToolData* tool);
	   void ReadToolMainTipOffset(XmlDocument^ Document, misStrctToolData* tool);
	   void ReadToolCurrentTipOffset(XmlDocument^ Document, misStrctToolData* tool);
	   void ifShouldForce2Calibrate(XmlDocument^ Document, misStrctToolData* tool);
	   void ifUseScaler(XmlDocument^ Document, misStrctToolData* tool);
	   void adjustNavigationRing(XmlDocument^ Document, misStrctToolData* tool);
	   void adjustToolDisplayProperties(XmlDocument^ Document, misStrctToolData* tool);
	   void determineToolBodyType(XmlDocument^ Document, misStrctToolData* tool);
	   void determineToolApplicationType(misStrctToolData* tool);

public:
	//misComPortSettingRW(void);
	//misAddTrackerToolRW(void);
	misXMLIO(misApplicationSetting* pApp);
 
	//misToolPropertiesListTypdef   ReadToolsLoadingProperties(misSimpleToolNameListTypdef   primeryTools, string path );
	 System::IntPtr   ReadToolsLoadingProperties(System::IntPtr  primeryTools, char* path );


	 void SaveTrackerToolData(misStrctToolData ToolData,System::String^ Address);
	 misStrctToolData ReadToolData(String^ Address);

	//static misStrctConnectOption ComPortSettingReader(char* Address);
	 System::IntPtr ComPortSettingReader(char* Address);
	 void ComPortSettingWriter(misStrctConnectOption port,char* Address);
	//static bool ComPorTInitialize(igstk::SerialCommunication::Pointer Port);		//Removed to Polaris Tracker due to native conflict
	 void writeCalibrationResults2XMLfile(System::String^ ToolRomFilesAddress, double calirationOffsetXYZ[3]);
	 void writeOrientationCalibrationResults2XMLfile(System::String^ ToolRomFilesAddress, misOrientationCalibrationDataTypdef OrientationCalibrationTransforms);
	 deque<misStrctTool>						UploadToolDataXMLContents(System::String^ Add);
	
};
	   // misApplicationSetting* misXMLIO::m_AppSetting=0;
#endif //MISXMLIO_H_HEADER_INCLUDED

