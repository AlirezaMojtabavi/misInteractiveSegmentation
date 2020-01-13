///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __startupformbase__
#define __startupformbase__

#include <wx/intl.h>

#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/string.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/hyperlink.h>
#include <wx/font.h>
#include <wx/stattext.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

namespace GNC
{
	namespace GUI
	{
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class StartUpFormBase
		///////////////////////////////////////////////////////////////////////////////
		class StartUpFormBase : public wxPanel 
		{
			private:
			
			protected:
				wxBoxSizer* m_pSizerToolBar;
				wxHyperlinkCtrl* m_hyperlink2;
				wxStaticText* m_staticText9;
				wxHyperlinkCtrl* m_hyperlink3;
				
				
				// Virtual event handlers, overide them in your derived class
				virtual void OnEraseBackground( wxEraseEvent& event ) { event.Skip(); }
				virtual void erasdf( wxHyperlinkEvent& event ) { event.Skip(); }
				
			
			public:
				wxBoxSizer* m_pSizerCenter;
				
				StartUpFormBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 548,288 ), long style = wxTAB_TRAVERSAL );
				~StartUpFormBase();
			
		};
		
	} // namespace GUI
} // namespace GNC

#endif //__startupformbase__
