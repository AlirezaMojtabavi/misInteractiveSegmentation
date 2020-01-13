#ifndef _MISPACSEXPLORERWINDOW
#define _MISPACSEXPLORERWINDOW

#include "misDicomViewerPanelManager.h"
#include "misPACSSettings.h"
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;

public ref class misPacsExplorerWindowGUI
{
public:

	virtual  void MappingEvents(); 
 
	bool					isDownloaded;


	void AddPatientstoTree (void);
	void AddSeriesToTree( GUIElement::Classes::misTreeViewItem^ tmpitm );
	void AddImagesToTree( GUIElement::Classes::misTreeViewItem^ tmpitm );

	//A pointer to GUI representation of misPacsExplorerWindow
	PacsGUILIbrary::misPacsExplorerWindow^ m_mainWindow;
	misPacsExplorerWindowGUI(PacsGUILIbrary::misPacsExplorerWindow^ window);

	PacsGUILIbrary::misPACSSetting^ m_pacsSettingWindow;

	misDicomViewerPanelManager	*m_PanelManager;

protected:
	int                             m_interval;
	int                             selectedTreeViewItemIndex;
	bool							isInitialized;
	String^							modalityToSearch;
	String^							fieldToSearch;
	String^							dateToSearch;
	String^							currStudyUID;
	String^							currSeriesUID;
	String^							currImageUID;
	bool							isStudySelected;
	bool							isSeriesSelected;
	System::Environment::SpecialFolder^       m_LastSelectedPath;

	void misButton_Download_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);
	void DownloadSelectedItem(String^ downloadMode, String^ UID);
	void ComboBoxServers_ItemClick(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);


private:

	
	void UserControl_PacsExplorer_Loaded(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void InitializePacs(bool isFirstTime);
	void ComboBoxServers_SelectionChanged(System::Object^ sender,System::Windows::Controls::SelectionChangedEventArgs^ arg);
	void StudyItem_DoubleClick(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void StudyItem_Click(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void SeriesItem_DoubleClick(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void SeriesItem_Click(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void ExtractUIDFromItem( GUIElement::Classes::misTreeViewItem^ item );
	void misButton_Refresh_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);
	void misButton_Search_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);
	void TextBox_Search_KeyUp(System::Object^ sender, System::Windows::Input::KeyEventArgs^ arg);

	void RadioButton_CT_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_MR_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_All_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_Name_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_ID_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );

	void RadioButton_AnyDate_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_today_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_todayAM_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_todayPM_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_yesterday_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_lastWeek_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_lastMonth_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_last3Months_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_last6Months_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );
	void RadioButton_between_Checked( System::Object^ sender,System::Windows::RoutedEventArgs^ arg );

	void pacsSetting_Close_MouseLeftButtonUp( System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg );
	void PACSSettingMappingEvents();
	void pacsSetting_OK_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);

	std::string GetPACSSettingXmlFilePath();

	void misButton_PACSSettings_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);

	void ShowPACSSettingWindow(misPACSSettings* pacSSetting);

	void WritePACSSettingToXmlFile(misPACSSettings* pacsSetting);
		misPACSSettings misPacsExplorerWindowGUI::ReadPACSSettingFromXmlFile();
	void DataGrid_PacsPatients_SelectionChanged(System::Object^ sender, System::Windows::Controls::SelectionChangedEventArgs^ arg);
	void StudyItem_Expanded(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void SeriesItem_Expanded(System::Object^ sender, System::Windows::RoutedEventArgs^ arg);
	void ImageItem_Click(System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg);
	void CancelWaitingBar( System::Object^ sender, System::Windows::Input::MouseButtonEventArgs^ arg );
	bool IsSearchSuccessed();


	misProgressBarGUI^       m_Progress;
	WarpperEntSpine::misMessageBox^	m_MessageBox;
	misPACSSettings* m_PacSSetting;
	std::vector<misPACS::PatientStrct>*  m_CurrentPateints;
	std::vector<misPACS::SeriesStrct>* m_CurrStudySeries;
	std::vector<std::string>* m_CurrSeriesImages;
	void DeletePreviuosPACSTempDirectory();
};





#endif
