/*
 *  
 *  $Id: openwithdialog.h $
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
#pragma once
#include "historypanel3base.h"
#include <utility>
#include <main/controllers/controladorextensiones.h>
#include <wx/msgdlg.h>
#include <wx/ginkgostyle/ginkgostyle.h>

//----------DIALOGO CONFIRMAR ELIMINAR...-------------
namespace GNC {
	namespace GUI {
		class OpenWithDialog: public OpenWithDialogBase {
		public:
			typedef std::list<std::pair<std::string,std::string> > ListaModalidades;
			OpenWithDialog(wxWindow* parent, ListaModalidades& listaModalidades) : 
					OpenWithDialogBase(parent),
					m_seleccionado(false)
			{
				//se buscan los modulos modos que abren la modalidad
				GNC::ControladorExtensiones::ListaModulos listaModulos = ControladorExtensiones::Instance()->Modulos();
				for(GNC::ControladorExtensiones::IteradorListaModulos itModulos=listaModulos.begin();itModulos!=listaModulos.end();++itModulos){
					for(GNC::GCS::IModuleController::IteradorListaModos itModos=(*itModulos).second->GetListaModos().begin();itModos!=(*itModulos).second->GetListaModos().end();++itModos){
						bool soporta = true;
						for(ListaModalidades::iterator itModalidad = listaModalidades.begin(); itModalidad != listaModalidades.end() && soporta; ++itModalidad) {
							soporta = soporta && (*itModos)->SupportsModalityFile((*itModalidad).first, (*itModalidad).second);
						}
						if(soporta){
							wxString wxStr = wxString::FromUTF8((*itModos)->GetDescripcion().c_str());
							m_pListaVistas->AppendString(wxStr);
							m_modulos.push_back((*itModulos).second);
							m_modos.push_back((*itModos));
						}
					}
				}
				if(m_pListaVistas->GetCount() > 0) {
					m_pListaVistas->Select(0);
				}
				m_pCheckUtilizarSiempre->Show(false);

				m_pPanelTitulo->Layout();
				Layout();
			}

			~OpenWithDialog(){
				m_modulos.clear();
				m_modos.clear();
			}

			void OnAceptarClick(wxCommandEvent &event){
				m_seleccionado = m_pListaVistas->GetSelection();
				if(m_seleccionado >=0 && m_seleccionado < (int)m_modos.size()){
					/*if(m_pCheckUtilizarSiempre->IsChecked()){
						wxConfigBase* config = wxConfigBase::Get();
						wxString clave = wxT("/GinkgoCore/Historial/AbrirCon/") + wxString::FromUTF8(m_modalidad.c_str()) + wxT("/");
						config->Write(clave + wxT("Modulo"),m_modulos[m_seleccionado]->GetUID());
						config->Write(clave + wxT("Modo"),m_modos[m_seleccionado]->GetId());
					}*/
					EndModal(wxID_OK);
				} else {
					wxMessageBox(_("Select a View"), _("Info"),
						 wxOK | wxICON_INFORMATION, this);
					event.Skip(false);
				}
			}

			GNC::GCS::IModuleController* GetModuloSeleccionado(){
				return m_modulos[m_seleccionado];
			}

			GNC::GCS::ModoControlador* GetModoSeleccionado(){
				return m_modos[m_seleccionado];
			}

		protected:
			typedef std::vector<GNC::GCS::IModuleController*> TipoVectorModulos;
			typedef std::vector<GNC::GCS::ModoControlador*> TipoVectorModos;
			TipoVectorModulos m_modulos;
			TipoVectorModos m_modos;
			int m_seleccionado;
		};
	}
}
