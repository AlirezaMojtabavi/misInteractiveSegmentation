///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 17 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __pasoscalibradobase__
#define __pasoscalibradobase__

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#undef __DEPRECATED
#include <vtkRenderer.h>
#include <wxVTKRenderWindowInteractor.h>
#include <vtk/vtkginkgoimageviewer.h>

///////////////////////////////////////////////////////////////////////////

namespace GNC
{
	namespace GUI
	{
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class ProcesarCalibradoBase
		///////////////////////////////////////////////////////////////////////////////
		class ProcesarCalibradoBase : public wxPanel 
		{
			private:
			
			protected:
				
				wxStaticText* m_staticText1;
				wxGauge* m_pProgreso;
				wxStaticText* m_pLabelProgreso;
			
			public:
				
				ProcesarCalibradoBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL );
				~ProcesarCalibradoBase();
			
		};
		
		///////////////////////////////////////////////////////////////////////////////
		/// Class RefinarCalibradoBase
		///////////////////////////////////////////////////////////////////////////////
		class RefinarCalibradoBase : public wxPanel 
		{
			private:
			
			protected:
				wxVTKRenderWindowInteractor* ViewInteractor2D;
				vtkGinkgoImageViewer* ViewImage2D;
			
			public:
				
				RefinarCalibradoBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL );
				~RefinarCalibradoBase();
			
		};
		
	} // namespace GUI
} // namespace GNC

#endif //__pasoscalibradobase__
