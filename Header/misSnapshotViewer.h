#pragma once

#include "misFilmStripPreparation.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace misMediaViewer;

namespace misMediaViewer{
public ref class misSnapshotViewer
{
private:
	System::Windows::Controls::Image^ m_Image_Current;
	System::Windows::Controls::TextBlock^ m_TextBlock_CurrentImageName;
	System::Windows::Controls::TextBlock^ m_TextBlock_CurrentImageIndex;
	System::Windows::Controls::TextBlock^ m_TextBlock_CurrentPage;

	System::Windows::Controls::ScrollViewer^ m_ScrollViewer_ThumbnailContainer;

	System::Windows::Controls::TextBlock^ m_TextBlock_DataManager;
	System::Windows::Controls::TextBlock^ m_TextBlock_AnalysingStudio;
	System::Windows::Controls::TextBlock^ m_TextBlock_Tracking;
	System::Windows::Controls::TextBlock^ m_TextBlock_Planning;
	System::Windows::Controls::TextBlock^ m_TextBlock_Registration;
	System::Windows::Controls::TextBlock^ m_TextBlock_Navigation;
	System::Windows::Controls::TextBlock^ m_TextBlock_All;

	String^ m_DataManager;
	String^ m_AnalysingStudio;
	String^ m_Tracking;
	String^ m_Planning;
	String^ m_Registration;
	String^ m_Navigation;
	String^ m_All;

	GUIElement::misButton^ m_misButton_NextImage;
	GUIElement::misButton^ m_misButton_PreviousImage;
	GUIElement::misButton^ m_misButton_DeleteAllSnapshots;
	GUIElement::misButton^ m_misButton_DeleteSelectedSnapshot;
	GUIElement::misButton^ m_misButton_PreviousPage;
	GUIElement::misButton^ m_misButton_NextPage;

	String^ m_SnapShotExtension;
	String^ m_snapShotsPath;

	void MakeAllControlsDisable();
	void PrepareControlsForFilmStrip();
	void MakeCategorySelected(System::Object^ sender);
	void FillFilmStrip(array<String^>^ pathsList);
	void GoToFirstSnapshot();
	void SnapshotsNextPage();
	void SnapshotsPrevPage();

	void misButton_PreviousImage_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_NextImage_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_DeleteSelectedSnapshot_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_DeleteAllSnapshots_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_ExportAllSnapshots_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_PreviousPage_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_NextPage_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);

	void TextBlock_Category_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	

	//long long GetAvailableDiskSpace(String^ path);
	//long GetDirectorySize(String^ path);
		
	array<String^>^ GetSnapshotsPathsByCategory(String^ categoryString);
	
	void SelectedThumbnail_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	
	array<String^>^ m_allSnapshotsPath;
	String^ ImagePath;
	int m_currentImageIndex;
	System::Windows::Controls::Primitives::UniformGrid^ m_UniformGrid_Thumbnails;
	String^ m_currentCategoryString;

	misFilmStripPreparation^ snapshotFilmStrip ;

public:
	misSnapshotViewer(void);
	
	void SetDefaultValues();

	bool m_IsInitialized;

	void SetImageCurrent(System::Windows::Controls::Image^ Image_Current);
	void SetTextBlockCurrentImageName(System::Windows::Controls::TextBlock^ TextBlock_CurrentImageName);
	void SetTextBlockCurrentImageIndex(System::Windows::Controls::TextBlock^ SetTextBlockCurrentImageIndex);
	void SetTextBlockCurrentPage(System::Windows::Controls::TextBlock^ SetTextBlockCurrentPage);
	void SetScrollViewer(System::Windows::Controls::ScrollViewer^ Scroll_Viewer_ThumbnailContainer);
	
	//********** SetCategoriesStrings must call before SetCategoriesTextBlocks ************
	void SetCategoriesStrings(
		String^ dataManager,
		String^ analysingStudio,
		String^ planning,
		String^ registration,
		String^ tracking,
		String^ navigation,
		String^ all
		);

	void SetCategoriesTextBlocks(
		System::Windows::Controls::TextBlock^ TextBlock_DataManager, 
		System::Windows::Controls::TextBlock^ TextBlock_AnalysingStudio, 
		System::Windows::Controls::TextBlock^ TextBlock_Planning, 
		System::Windows::Controls::TextBlock^ TextBlock_Registration, 
		System::Windows::Controls::TextBlock^ TextBlock_Tracking, 
		System::Windows::Controls::TextBlock^ TextBlock_Navigation, 
		System::Windows::Controls::TextBlock^ TextBlock_All);
	void SetNextPreviousButtons(GUIElement::misButton^ misButton_NextImage, GUIElement::misButton^ misButton_PreviousImage);
	void SetDeleteButtons(GUIElement::misButton^ misButton_DeleteSelectedSnapshot, GUIElement::misButton^ misButton_DeleteAllSnapshots);
	void SetNextPreviousPageButtons(GUIElement::misButton^ misButton_NextPage, GUIElement::misButton^ misButton_PreviousPage);

	void SetSnapShotsPath(String^ path);
	void SetSnapshotsExtension(String^ extension);
	void InitializeSnapshotViewer(bool checkSnapshotPath);

	void MappingEvents();
};
}


