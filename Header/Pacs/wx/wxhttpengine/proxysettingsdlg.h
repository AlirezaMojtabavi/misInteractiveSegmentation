/////////////////////////////////////////////////////////////////////////////
// Name:        proxysettingsdlg.h
// Purpose:     Simple proxy settings dialog for use with gui and wxHTTPBuilder
// Author:      Angelo Mandato
// Created:     2005/08/10
// RCS-ID:      $Id$
// Copyright:   (c) 2005 Angelo Mandato (http://www.spaceblue.com)
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_PROXYSETTINGSDLG_H_
#define _WX_PROXYSETTINGSDLG_H_

// optimization for GCC
#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "proxysettingsdlg.h"
#endif

#include <wx/dialog.h>
#include <wx/checklst.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/intl.h>
#include <api/api.h>
#include "wx/wxhttpengine/httpbuilder.h"

class EXTAPI wxProxySettingsDlg : public wxDialog
{

public:
	void OnRequiresAuthentication( wxCommandEvent &event );
	bool IsAuthProxy(void);
	void SetAuthProxy( const bool auth = true );

  // Properties
	wxString GetPassword(void);
	wxString GetUsername(void);
	wxString GetHost(void);
  long GetPortNumber(void);
  wxString  GetHostExceptions(void);
  wxProxySettings GetProxySettings(void);

	void SetPassword( const wxString &password );
	void SetUsername( const wxString &username );
	void SetHost( const wxString &host );
	void SetPortNumber( const long port );
  void SetHostExceptions( const wxString &exceptions );
  void SetProxySettings(const wxProxySettings &settings);

  // Additional settings:
  void SetHostExceptionsDesc(const wxString &text);
  void SetHostExceptionsNote(const wxString &text);

  wxProxySettingsDlg(wxWindow* parent, wxWindowID id, const wxString& caption = _T("Proxy Settings"), const bool bShowNoProxyFor = true );
  virtual ~wxProxySettingsDlg();

  virtual void OnRadioSystemClick( wxCommandEvent& event );
  virtual void OnRadioManualClick( wxCommandEvent& event );

private:
	wxRadioButton* m_pRadioSystem;
	wxRadioButton* m_pRadioManual;

  wxTextCtrl        *m_tcHost;
  wxTextCtrl        *m_tcPort;
  wxCheckBox        *m_cbAuthenticate;
  wxTextCtrl        *m_tcUserName;
  wxTextCtrl        *m_tcPassword;

  wxTextCtrl        *m_tcExceptions;

  wxStaticText      *m_stExceptionsDesc;
  wxStaticText      *m_stExceptionsNote;

  wxProxySettings   m_settings;
  wxPanel*			  m_pSettingsPanel;

  DECLARE_EVENT_TABLE()
};

#endif
