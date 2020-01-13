///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __calibracionbase__
#define __calibracionbase__

#include <wx/intl.h>

class BodyPanel;
class FooterPanel;
class TitledPanel;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CalibracionBase
///////////////////////////////////////////////////////////////////////////////
class CalibracionBase : public wxDialog 
{
	private:
	
	protected:
		BodyPanel* m_pBody;
		wxPanel* m_pPanelEspera;
		
		wxStaticText* m_pLabelMensaje;
		
		TitledPanel* m_panelMedida;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_ControlDistancia;
		wxChoice* m_unidades;
		FooterPanel* m_pFooter;
		
		wxButton* m_pBotonAceptar;
		wxButton* m_pBotonCancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnActivate( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnDialogoKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnControlDistanciaKeyDown( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnBotonAceptarClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBotonCancelarClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CalibracionBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Calibration"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
		~CalibracionBase();
	
};

#endif //__calibracionbase__
