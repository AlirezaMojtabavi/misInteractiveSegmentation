#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Drawing::Imaging;
 

public ref class misTakeSnapShot
{
private :
	//specify image format ( file extension )
	System::Drawing::Imaging::ImageFormat^ m_ImageFormat;

	String^ m_SnapShotFolderStr;
	String^ SnapShotFileNameStr;

	String^ GetImageFormatInString(void);

public:
	void  ResetSetting(void);
	      misTakeSnapShot(void);
	//Get a snap shot from current viewing scene
	void     TakeSnapShot( String^ tabName, String^ subTabName );

	 String^ GetPatientSnapshotFolderDirectory();
	 void    SetPatientSnapshotFolderDirectory(String^ path);

	 void SetImageFormat(System::Drawing::Imaging::ImageFormat^ format);
	 System::Drawing::Imaging::ImageFormat^ ConvertToImageFormat(std::string imgFormatStr);
	 System::Drawing::Imaging::ImageFormat^ GetImageFormat();

	 static System::Drawing::Imaging::ImageCodecInfo^ GetEncoderInfo( ImageFormat^ format );
};
