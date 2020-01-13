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

namespace misMediaViewer{

public ref class misVideoViewer
{

private:

	System::Windows::Controls::MediaElement^ m_MediaElement_video;

	System::Windows::Controls::ProgressBar^ m_ProgressBar_ElapseTime;

	System::Windows::Controls::Image^ m_Image_NoVideo;
	System::Windows::Controls::TextBlock^ m_TextBlock_CurrentVideoName;
	System::Windows::Controls::TextBlock^ m_TextBlock_CurrentVideoIndex;
	System::Windows::Controls::TextBlock^ m_TextBlock_CurrentPage;

	System::Windows::Controls::ScrollViewer^ m_ScrollViewer_ThumbnailContainer;

	System::Windows::Controls::Slider^ m_Sliser_Timeline;

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

	GUIElement::misButton^ m_misButton_NextVideo;
	GUIElement::misButton^ m_misButton_PreviousVideo;
	GUIElement::misButton^ m_misButton_Play;
	GUIElement::misButton^ m_misButton_Pause;
	GUIElement::misButton^ m_misButton_DeleteAllVideos;
	GUIElement::misButton^ m_misButton_DeleteSelectedVideo;
	GUIElement::misButton^ m_misButton_ScreenShot;
	GUIElement::misButton^ m_misButton_PreviousPageV;
	GUIElement::misButton^ m_misButton_NextPageV;

	WarpperEntSpine::misMessageBox^ m_MessageBox;

	String^ m_videoExtension;
	String^ m_videosPath;
	String^ m_snapshotsPath;
	String^ m_snapshotExtension;
	String^ m_NavigationSnapshotCategoryName;

	void MakeAllControlsDisable();
	void PrepareControlsForFilmStrip();
	void MakeCategorySelected(System::Object^ sender);
	void FillFilmStrip(array<String^>^ pathsList);
	void GoToFirstVideo();
	void VideosNextPage();
	void VideosPrevPage();

	void misButton_PreviousVideo_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_NextVideo_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_Play_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_Pause_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_ScreenShot_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_DeleteSelectedVideo_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_DeleteAllVideos_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void misButton_PreviousPageV_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_NextPageV_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);
	void TextBlock_Category_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);	
	void MediaElement_MediaOpened(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void MediaElement_MediaEnded(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);

	bool m_isSliderDragging;

	void SliderDragStarted(System::Object^ sender, System::Windows::Controls::Primitives::DragStartedEventArgs^ arg);
	void SliderDragCompleted(System::Object^ sender, System::Windows::Controls::Primitives::DragCompletedEventArgs^ arg);

	array<String^>^ GetVideosPathsByCategory(String^ categoryString);

	void SelectedThumbnail_MouseLeftButtonUp(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);

	array<String^>^ m_allVideosPath;

	int m_currentVideoIndex;
	System::Windows::Controls::Primitives::UniformGrid^ m_UniformGrid_Thumbnails;
	String^ m_currentCategoryString;

	misMediaViewer::misFilmStripPreparation^ videoFilmStrip ;

	void EmittPulse(Object^ sender,System::EventArgs^ e);
	void PlayVideo(GUIElement::misFilmStripItem^ filmStripVideoItem);

	DispatcherTimer^ m_timer;

public:

	misVideoViewer(void);

	void SetMediaElement(System::Windows::Controls::MediaElement^ mediaElement_Video);
	void SetImageNoVideo(System::Windows::Controls::Image^ Image_Novideo);
	void SetTextBlockCurrentVideoName(System::Windows::Controls::TextBlock^ TextBlock_CurrentVideoName);
	void SetTextBlockCurrentVideoIndex(System::Windows::Controls::TextBlock^ SetTextBlockCurrentVideoIndex);
	void SetTextBlockCurrentPage(System::Windows::Controls::TextBlock^ SetTextBlockCurrentPage);
	void SetScrollViewer(System::Windows::Controls::ScrollViewer^ Scroll_Viewer_ThumbnailContainer);
	void SetSliderTimeline(System::Windows::Controls::Slider^ sliser_Timeline);
	void SetProgressBarElapsedTime(System::Windows::Controls::ProgressBar^ progressBar);
	void Slider_Timeline_ValueChanged(System::Object^ sender, System::Windows::RoutedPropertyChangedEventArgs<double>^ e);
	GUIElement::Classes::DragStarted^   GetDragStarted();
	GUIElement::Classes::DragCompleted^  GetDragCompleted();

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
	void SetNextPreviousButtons(GUIElement::misButton^ misButton_NextVideo, GUIElement::misButton^ misButton_PreviousVideo);
	void SetPlayPauseButtons(GUIElement::misButton^ misButton_Play, GUIElement::misButton^ misButton_Pause);
	void SetDeleteButtons(GUIElement::misButton^ misButton_DeleteSelectedVideo, GUIElement::misButton^ misButton_DeleteAllVideos);
	void SetScreenShotButton(GUIElement::misButton^ misButton_ScreenShot);

	void SetVideosPath(String^ path);
	void SetSnapshotsPath(String^ path);
	void SetNavigationSnapshotsCategoryName(String^ name);

	void SetNextPreviousPageButtons(GUIElement::misButton^ misButton_NextPage, GUIElement::misButton^ misButton_PreviousPage);

	void SetVideosExtension(String^ extension);

	void InitializeVideoViewer();

	void MappingEvents();
	String^ GetScreenShotFileName();

	void SetSnapshotsExtension( String^ snapshotsExtension );
	String^ GetDateTimeString( DateTime currentDateTime );
};
}


