#pragma once

#include <list>
#include "misGuiWrapper.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Interop;
using namespace  System::Windows::Threading;
using namespace  System::Windows::Media::Imaging;

public ref class misSnapshotFilmStripPreparation/* : public misGuiWrapper*/
{

private:	

	array<String^>^ m_PathList;
	System::Windows::Controls::ScrollViewer^ m_ScrollViewer_ThumbnailContainer;	
	System::Threading::Thread^ loadImageThread;
	int m_LastPosition;
	int m_FirstPosition;
	int m_CurrentPosition;

	void LoadImages();
	void RenderImage(int index);
	void SelectedThumbnail_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void MakeSnapshotSelected(int index);

	bool isInitialized;

public:

	System::Windows::Controls::Primitives::UniformGrid^ m_UniformGrid_Thumbnails;

	misSnapshotFilmStripPreparation(void);
	void SetContainer(System::Windows::Controls::ScrollViewer^ scrollViewer);
	void SetPathList(array<String^>^ pathsList);
	void FillFilmStrip();
	void Reset();
	void GoToNextSnapshot();
	void GoToPreviousSnapshot();
	bool IsLastPosition();
	bool IsFirstPosition();
	GUILibrary::misSnapshotItem^  GetCurrentSnapshot();
	void SetCurrentPositionIndex(int index)	;
	void GoToFirstSnapshot();

	void ShowNoImageToPreviewMessage();
};



