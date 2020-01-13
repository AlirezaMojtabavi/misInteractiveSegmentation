///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version May  4 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __dicombrowsercomponentbase__
#define __dicombrowsercomponentbase__

#include <wx/intl.h>

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
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

namespace GNC
{
	namespace GUI
	{
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class DicomBrowserComponentBase
		///////////////////////////////////////////////////////////////////////////////
		class DicomBrowserComponentBase : public wxPanel 
		{
			private:
			
			protected:
				wxTreeListCtrl* m_pTreeListIzq;
				wxButton* m_button8;
				wxButton* m_button51;
				wxButton* m_button6;
				wxButton* m_button7;
				wxTreeListCtrl* m_pTreeListDer;
				
				// Virtual event handlers, overide them in your derived class
				virtual void OnDicomDirIzqAddAll( wxCommandEvent& event ) { event.Skip(); }
				virtual void OnAdd( wxCommandEvent& event ) { event.Skip(); }
				virtual void OnDel( wxCommandEvent& event ) { event.Skip(); }
				virtual void OnDicomDirDerDelAll( wxCommandEvent& event ) { event.Skip(); }
				
			
			public:
				
				DicomBrowserComponentBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 548,288 ), long style = wxTAB_TRAVERSAL );
				~DicomBrowserComponentBase();
			
		};
		
	} // namespace GUI
} // namespace GNC

#endif //__dicombrowsercomponentbase__
