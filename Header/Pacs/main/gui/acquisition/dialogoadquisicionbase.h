///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dialogoadquisicionbase__
#define __dialogoadquisicionbase__

#include <wx/intl.h>

class BodyPanel;
class FooterPanel;
class HeaderPanel;
class TitledPanel;
class wxTreeListCtrlAcquisition;

#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/srchctrl.h>
#include <wx/sizer.h>
#include <wx/radiobut.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/statbox.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/treelistctrl/treelistctrl.h>
#ifdef __VISUALC__
#include <wx/link_additions.h>
#endif //__VISUALC__
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listbox.h>

#include "wxtreelistctrlacquisition.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class DialogoAdquisicionBase
///////////////////////////////////////////////////////////////////////////////
class DialogoAdquisicionBase : public wxDialog 
{
	private:
	
	protected:
		wxBoxSizer* m_pMainSizer;
		HeaderPanel* m_pHeader;
		BodyPanel* m_pBodyPanel;
		TitledPanel* m_pPanelPACS;
		wxStaticText* m_pPatientLabelStr;
		wxComboBox* m_pFieldCombo;
		wxSearchCtrl* m_pTextControlField;
		wxStaticText* m_pLabelRestricted;
		wxBoxSizer* m_pSizerAnimation;
		wxStaticText* m_pServerLabel;
		wxComboBox* m_pPACSListaServidores;
		wxRadioButton* m_pAnyDate;
		wxRadioButton* m_pTodayAM;
		wxRadioButton* m_pTodayPM;
		wxRadioButton* m_pToday;
		wxRadioButton* m_pYesterday;
		wxRadioButton* m_pLastWeek;
		wxRadioButton* m_pLastMonth;
		wxRadioButton* m_pLastThreeMonths;
		wxRadioButton* m_pBetween;
		wxDatePickerCtrl* m_pTextControlFechaDesde;
		wxDatePickerCtrl* m_pTextControlFechaHasta;
		wxGridSizer* m_pModalitySizer;
		wxTreeListCtrlAcquisition* m_pTreeListResultados;
		
		wxButton* m_pBLink;
		wxButton* m_pBDescargar;
		FooterPanel* m_pFooter;
		
		wxButton* m_pBotonClose;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnKeyDownFormulario( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnComboField( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancelClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBusquedaClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnPACSChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFechaDesdeDateChanged( wxDateEvent& event ) { event.Skip(); }
		virtual void OnFechaHastaDateChanged( wxDateEvent& event ) { event.Skip(); }
		virtual void OnLinkClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDescargarClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCloseClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DialogoAdquisicionBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("DICOM Query/Retrieve"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 950,575 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
		~DialogoAdquisicionBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DialogoNotFoundBase
///////////////////////////////////////////////////////////////////////////////
class DialogoNotFoundBase : public wxDialog 
{
	private:
	
	protected:
		TitledPanel* m_panel5;
		wxStaticText* m_staticText10;
		
		
		wxButton* m_button10;
	
	public:
		wxListBox* m_pListaSeries;
		FooterPanel* m_pPanelOkCancel;
		wxButton* m_pButtonOk;
		wxButton* m_pButtonCancel;
		FooterPanel* m_pPanelOk;
		
		DialogoNotFoundBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Not found"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~DialogoNotFoundBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DownloadAgainDialogBase
///////////////////////////////////////////////////////////////////////////////
class DownloadAgainDialogBase : public wxDialog 
{
	private:
	
	protected:
		HeaderPanel* m_pHeader;
		BodyPanel* m_pBody;
		TitledPanel* m_pFormPanel;
		wxStaticText* m_pLabelMessage;
		FooterPanel* m_panel6;
		
		wxButton* m_button9;
		wxButton* m_pButtonOk;
		wxButton* m_pBotonCancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnOpenClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		DownloadAgainDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Download again"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~DownloadAgainDialogBase();
	
};

#endif //__dialogoadquisicionbase__
