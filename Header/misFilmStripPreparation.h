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
using namespace System::Windows::Interop;
using namespace System::Windows::Threading;
using namespace System::Windows::Media::Imaging;

namespace misMediaViewer{

public enum class FilmStripFileTypeEnum
{
	ImageType,
	VideoType
};


public ref class misFilmStripPreparation
{

private:	

	array<String^>^ m_PathList;
	System::Windows::Controls::ScrollViewer^ m_ScrollViewer_ThumbnailContainer;	
	System::Threading::Thread^ loadImageThread;
	String^ m_extensionString;
	misMediaViewer::FilmStripFileTypeEnum m_extensionType;

	void LoadImages();
	void RenderImage(int index);
	void SelectedThumbnail_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	int MakeItemSelected(int index);

	bool isInitialized;
	System::Threading::Mutex^  m_ThreadLock;
	bool  m_AbortThread;

public:
	int m_LastPosition;
	int m_FirstPosition;
	int m_CurrentPosition;

	System::Windows::Controls::Primitives::UniformGrid^ m_UniformGrid_Thumbnails;

	misFilmStripPreparation(misMediaViewer::FilmStripFileTypeEnum type);
	void SetContainer(System::Windows::Controls::ScrollViewer^ scrollViewer);
	void SetPathList(array<String^>^ pathsList);
	void SetExtension(String^ extensionString);
	void FillFilmStrip();
	void Reset();
	int GoToNextItem();
	int GoToPreviousItem();
	int GetItemsCount();
	bool IsLastPosition();
	bool IsFirstPosition();
	GUIElement::misFilmStripItem^  GetCurrentItem();
	void SetCurrentPositionIndex(int index)	;
	void GoToFirstItem();

	void ShowNoItemToPreviewMessage();
};

}

