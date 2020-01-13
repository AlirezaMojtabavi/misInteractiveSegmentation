/*
 *  
 *  $Id: printmanager.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 *
 */
#include <api/globals.h>
#include <api/math/geometry.h>

#include <api/ivista.h>
#include <map>

#include <wx/print.h>
#include <wx/dc.h>

class wxCheckBox;
class wxCheckListBox;
class wxBoxSizer;
class wxSlider;
class wxButton;
class wxChoice;
class SubTitledPanel;
class wxStaticText;

namespace GNC {
	namespace GCS {
		class IImageExportDelegate;
		namespace Printing {
			struct TipoWizardImprimir;
			struct MemoryBitmap;
		/*	class Posicion {
			public:
				Posicion(unsigned int x = 0, unsigned int y = 0)
				{
					m_x = x;
					m_y = y;
				}

				Posicion(const Posicion& o)
				{
					*this = o;
				}

				inline bool operator < (const Posicion& o) const 
				{
					return ( (m_x < o.m_x) && (m_y < o.m_y) );
				}

				inline bool operator <= (const Posicion& o) const 
				{
					return !(*this > o);
				}

				inline bool operator > (const Posicion& o) const
				{
					return ( (m_x > o.m_x) && (m_y > o.m_y) );
				}

				inline bool operator >= (const Posicion& o) const 
				{
					return !(*this < o);
				}

				inline bool operator == (const Posicion& o) const {
					return ( (m_x == o.m_x) && (m_y == o.m_y) );
				}

				inline bool operator != (const Posicion& o) const {
					return !(*this == o);
				}

				inline Posicion& operator = (const Posicion& o) {
					m_x = o.m_x;
					m_y = o.m_y;
					return (*this);
				}

			protected:
				unsigned int m_x;
				unsigned int m_y;
			};

			class Celda {
			public:
				Celda(const Posicion& pos = Posicion(0, 0), GNC::GCS::IVista* v = NULL)
				{
					m_Posicion = pos;
					m_Vista = v;
				}

				GNC::GCS::IVista* GetVista()
				{
					return m_Vista;
				}

				const Posicion& GetPosicion()
				{
					return m_Posicion;
				}

			private:
				Posicion m_Posicion;
				GNC::GCS::IVista* m_Vista;
			};

			class Layout {
			public:
				typedef std::map<Posicion, Celda> MapaCeldas;

				Layout()
				{
				}

				void AddView(int row, int col, GNC::GCS::IVista* pVista)
				{
					Posicion pos(row,col);
					m_Celdas[pos] = Celda(pos, pVista);

				}

				inline MapaCeldas& Celdas()
				{
					return m_Celdas;
				}

			private:
				MapaCeldas m_Celdas;
			};
*/
			class PrintManager : public wxPrintout {
			public:
				PrintManager(const wxString& titulo, wxPrintData* pPrintData);

				virtual ~PrintManager();

				bool HasPage(int page);

				bool OnBeginDocument(int startPage, int endPage);

				void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);

				virtual bool OnPrintPage(int page);

				void SetDatosExportacion(TipoWizardImprimir* pDatosExportacion);

				void RenderizaImagen(int page,MemoryBitmap* pMemoryBitmap, const GNC::GCS::Vector& size);

			protected:
				TipoWizardImprimir* m_pDatosExportacion;
				wxPrintData *m_pPrintData;
			};


			class DialogoImpresion : public wxPreviewFrame {
			public:
				DialogoImpresion(wxWindow *parent, GNC::GCS::Ptr<GNC::GCS::IImageExportDelegate>& pExportContract,const wxString& titulo, wxPrintData* pPrintDialog);

				~DialogoImpresion();

				virtual void CreateCanvas();
				virtual void Initialize();

			protected:
				void RefrescarSliders();
				
				void OnConfigurarPaginaClick(wxCommandEvent& event);
				void OnImprimirClick( wxCommandEvent& event );
				void OnCancelarClick( wxCommandEvent& event );
				void OnScrollPage ( wxScrollEvent& event);
				void OnZoomChoice( wxCommandEvent& event );
				void GoToPage(int page);
				void SetZoom(int position);
				void OnPaginasHoja( wxCommandEvent& event );
				void OnCheckCapasToggled( wxCommandEvent& event );
				void OnCheckWidgetsAnotacion( wxCommandEvent &event);

				//atributos de visualizacion
				std::list<int> m_zooms;

				PrintManager* m_printManagerPreview;
				PrintManager* m_printManagerImpresion;

				wxCheckBox* m_pIncluirWidgets;
				wxStaticText* m_pTituloMapas;
				wxStaticText* m_pLabelPagina;
				wxChoice* m_pZooms;
				wxCheckListBox* m_pMapasCheck;
				wxBoxSizer* m_pSizerPrevisualizacion;
				SubTitledPanel* m_pPanelPrevisualizacion;
				wxSlider* m_pSliderScroll;
				wxChoice* m_pPaginasHoja;
				wxButton* m_pBotonConfigurarPagina;
				wxButton* m_pBotonImprimir;
				wxButton* m_pBotonCancelar;

				//otros atributos
				TipoWizardImprimir* m_pDatosExportacion;
				wxPrintData* m_pPrintData;
			};
		}
	}
}
