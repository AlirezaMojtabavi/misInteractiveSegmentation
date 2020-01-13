/*
 *  
 *  $Id: wnota.h $
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
#include <cmath>
#include <api/iwidgets.h>
#include <api/widgetserializable.h>
#include <widgets/openglhelper.h>

//----------------------------------------------------------------------------------------------------
//region Forward Declarations
namespace GNC {
	namespace GCS {
		namespace Widgets {
			
			namespace Dialogos {
				class SeleccionTexto;
			}
			
			class WCajaTexto;
		}
	}
}
//endregion

namespace GNC {
	namespace GCS {
		namespace Widgets {

			namespace Dialogos {
				class SeleccionTexto;
			}

			class WCajaTexto;

			//====================================================================================================
			//= Builder de notas
			//====================================================================================================
			class WNotaBuilder : public GNC::GCS::Widgets::IWidgetBuilder {
			public:
				typedef GNC::GCS::Vector TVector;
				WNotaBuilder(GNC::GCS::IWidgetsManager* pManager, const GNC::GCS::TriggerButton& buttonMask);

				~WNotaBuilder();

				virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&);

				virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&);

				virtual void Render(GNC::GCS::Contexto3D* c);

				virtual GNC::GCS::Widgets::TipoCursor GetCursor();

			protected:
				TVector m_Posicion;
				GNC::GCS::Widgets::IWidgetBuilder::Estado m_Estado;
				bool m_MouseDown;

				WCajaTexto* m_pTempWidget;

			};

			//====================================================================================================
			//= Widget de notas
			//====================================================================================================
			class WCajaTexto : public GNC::GCS::Widgets::IWidget, public GNC::GCS::Widgets::IWidgetSerializable {

			public:
				typedef GNC::GCS::Vector TVector;
				typedef GNC::GCS::Matriz TMatriz;

				WCajaTexto(IWidgetsManager* pManager, long vid, TVector posicion, const char* nombre = "", std::string texto = "");

				~WCajaTexto();
				
			//----------------------------------------------------------------------------------------------------
			//region "Serializado y desserializado"
			public:
				WCajaTexto(IWidgetsManager* pManager, long vid, wxXmlNode* nodo);

				wxXmlNode* Serializar(const std::string& nombreMedico);
				void DoEditText(wxWindow* pWindow);
			//endregion

				TVector          m_Posicion;
				TVector          m_PosAntigua;

				TVector          m_Quad[4]; // Quad position in plane coordiantes

				GNC::GCS::Vector m_TamTexto;

				std::string      m_Texto;
				bool             m_Vacio;

				Color            m_Color;

				typedef struct TexturaNota {
					std::string texto;
					TexturaCairo* m_textura;
					bool	correcta;	//indica si esta correctamente cargada
					TexturaNota()
					{
						m_textura = new GNC::GCS::TexturaCairo();
						m_textura->ActivarInterpolacion();
						texto = "";
						correcta = false;
					}
					~TexturaNota()
					{
						m_textura->Descargar();
						delete m_textura;
					}
				} TexturaNota;
				typedef std::map<void*,TexturaNota*> TMapaRecursos;
				TMapaRecursos m_mapaRecursos;
				TexturaNota* GetTextura(void* renderer);
				void Invalidar();

				GNC::GCS::Widgets::Dialogos::SeleccionTexto* m_pWidgetSeleccion;

			protected:
				bool m_MouseDown;

				float m_AnchoMaximo;
				float m_TamFuente;
			

			//----------------------------------------------------------------------------------------------------
			//region "Colores"
			public:

				virtual void SetColor(Color color);
				virtual const std::string& GetTexto() const;
				virtual void SetTexto(const std::string& texto);
				virtual void PropagarModificacion();
				virtual const Color& GetColor() const;
			//endregion
				
			//----------------------------------------------------------------------------------------------------
			//region "Interfaz especifica"
			public:

				virtual bool SoportaAutoBorrado() const {
					return true;
				}

				virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&);

				virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&);

				virtual bool HitTest(float x, float y, const GNC::GCS::Vector& umbral);

				virtual bool HitTest(GNC::GCS::Vector* vertices, int numVertices);

				virtual void Render(GNC::GCS::Contexto3D* c);
				
				virtual void OffscreenRender(Contexto3D* c);

				virtual void Seleccionar(bool seleccionado);

				virtual void Iluminar(bool iluminado);

				virtual void Ocultar(bool oculto);
				
				virtual void LiberarRecursos(GNC::GCS::IWidgetsRenderer* pKey);

			//----------------------------------------------------------------------------------------------------
			//region "Helpers"
			public:
				virtual void Recalcular(void* renderer);
			//endregion

			//----------------------------------------------------------------------------------------------------
			//region "Menu contextual"
			public:
				virtual bool GetMenuContextual(wxMenu* , wxWindow* pParent) ;
			//endregion
				
				
				virtual void InsertarPropiedades(TListaMapasPropiedades &listaMapaPropiedades);

			};
		}
	}
}
