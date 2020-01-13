///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 16 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __editordicombase__
#define __editordicombase__

#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#ifdef __VISUALC__
#include <wx/link_additions.h>
#endif //__VISUALC__
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace GNC
{
	namespace GUI
	{
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class EditorDICOMBase
		///////////////////////////////////////////////////////////////////////////////
		class EditorDICOMBase : public wxDialog 
		{
			private:
			
			protected:
				wxCheckBox* m_pCheckAnonimizar;
				wxPanel* m_pPanelCampos;
				wxBoxSizer* m_pSizerCampos;
				wxCheckBox* m_pCheckConfiguracion;
				wxCheckBox* m_pCheckNombrePaciente;
				wxCheckBox* m_pCheckIdPaciente;
				wxCheckBox* m_pCheckInstituciones;
				wxCheckBox* m_pCheckComentarios;
				wxPropertyGrid* m_pListaAtributos;
				wxButton* m_button1;
				wxButton* m_button2;
				
				// Virtual event handlers, overide them in your derived class
				virtual void OnCheckAnonimizar( wxCommandEvent& event ){ event.Skip(); }
				virtual void OnCheckConfiguracion( wxCommandEvent& event ){ event.Skip(); }
				virtual void OnCheckNombreApellidos( wxCommandEvent& event ){ event.Skip(); }
				virtual void OnCheckIdPaciente( wxCommandEvent& event ){ event.Skip(); }
				virtual void OnCheckInstituciones( wxCommandEvent& event ){ event.Skip(); }
				virtual void OnCheckComentarios( wxCommandEvent& event ){ event.Skip(); }
				virtual void OnAceptarClick( wxCommandEvent& event ){ event.Skip(); }
				
			
			public:
				EditorDICOMBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Editar DICOM"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 827,546 ), long style = wxCAPTION|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU );
				~EditorDICOMBase();
			
		};
		
	} // namespace GUI
} // namespace GNC

#endif //__editordicombase__
