///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __taskcontrolbase__
#define __taskcontrolbase__

#include <wx/intl.h>

class FooterPanel;

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/treelistctrl/treelistctrl.h>
#ifdef __VISUALC__
#include <wx/link_additions.h>
#endif //__VISUALC__
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace GNC
{
	namespace GUI
	{
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class TaskControlBase
		///////////////////////////////////////////////////////////////////////////////
		class TaskControlBase : public wxDialog 
		{
			private:
			
			protected:
				wxTreeListCtrl* m_treeListCtrlTasks;
				FooterPanel* m_panel2;
				
				wxButton* m_button4;
				wxButton* m_button5;
				
				// Virtual event handlers, overide them in your derived class
				virtual void OnRefreshClick( wxCommandEvent& event ) { event.Skip(); }
				
			
			public:
				
				TaskControlBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Tasks"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,250 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER );
				~TaskControlBase();
			
		};
		
	} // namespace GUI
} // namespace GNC

#endif //__taskcontrolbase__
