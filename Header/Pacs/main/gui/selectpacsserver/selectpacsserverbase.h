///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __selectpacsserverbase__
#define __selectpacsserverbase__

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
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace GNC
{
	namespace GUI
	{
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class SelectPacsServerBase
		///////////////////////////////////////////////////////////////////////////////
		class SelectPacsServerBase : public wxDialog 
		{
			private:
			
			protected:
				BodyPanel* m_pBody;
				TitledPanel* m_pPanelMessage;
				wxStaticText* m_pLabel;
				wxChoice* m_pServer;
				FooterPanel* m_pFooter;
				
				wxButton* m_pOkButton;
				wxButton* m_button5;
			
			public:
				
				SelectPacsServerBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select PACS"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
				~SelectPacsServerBase();
			
		};
		
	} // namespace GUI
} // namespace GNC

#endif //__selectpacsserverbase__
