#ifndef misXmlParser_H
#define misXmlParser_H

//#include "tinyxml.h"
//#include <string>
//#include "misStrctPatientData.h"
//#include "misStrctImageData.h"
//#include <list>
//#include "misDataSetTypes.h"
//#include "misResultCode.h"
//#include "misIO.h"
//
//using namespace System;
//
//class misXmlParser
//{
//private:
//
//	static void SetMisImageingProperties(misImageingProperties imageingProperties,TiXmlElement* imageDataPropertiesElement);
//	static void SetMisPatientProperties(misPatientProperties patientProperties,TiXmlElement* imageDataPropertiesElement);
//	static void SetMisHardwareProperties(misHardwareProperties hardwareProperties,TiXmlElement* imageDataPropertiesElement);
//	static void SetMisImageProperties(misImageProperties imageProperties,TiXmlElement* imageDataPropertiesElement);
//	static void SetMisSerieProperties(misSerieProperties serieProperties,TiXmlElement* imageDataPropertiesElement);
//	static void SetMisStudyProperties(misStudyProperties studyProperties,TiXmlElement* imageDataPropertiesElement);
//	static void SetMisImageViewingProperties(misImageViewingProperties imageViewingProperties, TiXmlElement* imageDataPropertiesElement);
//	static void SetImageAddressNode(TiXmlElement* rootElement, string imageAddress);
//	static bool ValidateImageXmlFile(string fileName);
//	static bool ValidatePatientsXmlFile(string fileName);
//	static bool PrepareImageXmlFile(string fileName);
//	static bool PreparePatientsXmlFile(string fileName);
//	static TiXmlNode* LookUpForExisitingPatient(TiXmlElement* rootElement, misPatient patient);
//	static bool FileExists(string& fileName);
//	static misResultCode::ResultIds PreparePatientSolutionXmlFile(string fileName);
//	static bool AddImageDataToHybridPackage(misCompeleteImageDependencies  completeImageDepensiest);
//	static misResultCode::ResultIds ValidatePatientSolutionXmlFile(TiXmlDocument* patientSolutionXmlDocument);
//	static misResultCode::ResultIds SearchForExistingPolyData(TiXmlElement* hybridPackageElement, string polyDatatUID);
//	static misResultCode::ResultIds RetrieveHybridPackagesNode(string fileName, TiXmlElement* hybridPackagesElement);
//	static misResultCode::ResultIds RetrieveSpecificHybridPackage(TiXmlElement* hybridPackages, TiXmlElement* specificHybridPackage, string hybridPackageUID);
//	static misResultCode::ResultIds ReadHybridPackage(TiXmlElement* hybridPackage, misCompeleteImageDependencies * completeImageDepensiest, list<misCompeletePolyDataDependensiesStrct>* polyDataList);
//	static misResultCode::ResultIds SearchForSpecificHybridPackage(string fileName, string hybridPackageUID, TiXmlElement* hybridPackage);
//	static misResultCode::ResultIds DeleteSpecificHybridPackage(string fileName, string hybridPackageUID);
//
//public:
//
//	//-----------------------------
//
//	static TiXmlElement* FindSpecificNode( TiXmlElement* nodeToSearch, string specificNodeName);
//	static bool WriteImageXmlFile(string fileName, misImageDataProperties imageDataProperties, string imageAddress);
//	static bool ReadImageXmlFile(string fileName, misImageDataProperties* imageDataPropertiesToFill, string& imageAddress);
//	static bool WritePatientNodeInPatientsXmlFile(string fileName, misPatient patient);
//	static bool ReadPatientsXmlFile(string fileName,list<misPatient>* patientsList);
//	static misResultCode::ResultIds AddHybridPackage(string fileName, string hybridPackageName, string hybridPackageUID, misCompeleteImageDependencies * completeImageDepensiest, misCompeletePolyDataDependensiesStrct* compeletePolyDataDependensies);
//	static misResultCode::ResultIds AddPolyDataToHybridPackage(string fileName, string hybridPackageUID, misCompeletePolyDataDependensiesStrct* compeletePolyDataDependensies);
//	static misResultCode::ResultIds ReadSpecificHybridPackage(string fileName, string hybridPackageUID, misCompeleteImageDependencies * completeImageDepensiest, list<misCompeletePolyDataDependensiesStrct>* polyDataList);
//	static misResultCode::ResultIds ReadPolyDatasFromHybridPackage(TiXmlElement* hybridPackage, list<misCompeletePolyDataDependensiesStrct>* polyDataList);
//
//	//-----------------------------
//
//};
#endif