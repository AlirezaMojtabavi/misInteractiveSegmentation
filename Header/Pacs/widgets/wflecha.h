/*
 *  
 *  $Id: wflecha.h $
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
#include <api/iwidgets.h>
#include <widgets/openglhelper.h>
#include <api/widgetserializable.h>

// Forward Declarations
namespace GNC {
	namespace GCS {
		class IWidgetsManager;
	}
}
class vtkImageData;
// Forward Declarations

namespace GNC {
	namespace GCS {
		namespace Widgets {

			class WFlecha;

			class WFlechaBuilder : public GNC::GCS::Widgets::IWidgetBuilder {
			public:

				typedef GNC::GCS::Vector TVector;
				typedef GNC::GCS::Nodo   TNodo;
				typedef GNC::GCS::Matriz TMatriz;

				WFlechaBuilder(GNC::GCS::IWidgetsManager* pManager, const GNC::GCS::TriggerButton& buttonMask);

				~WFlechaBuilder();

				virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&);

				virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&);

				virtual void Render(GNC::GCS::Contexto3D* c);

				virtual GNC::GCS::Widgets::TipoCursor GetCursor();


			protected:

				bool                          m_MouseDown;
				WFlecha*                      m_pFlechaTemp;

			};

			class WFlecha : public GNC::GCS::Widgets::IWidget, public GNC::GCS::Widgets::IWidgetSerializable {

			public:
				GNC::GCS::Nodo m_Vertices[2];

//region "Constructor y destructor"

			public:

				typedef GNC::GCS::Vector TVector;
				typedef GNC::GCS::Matriz TMatriz;

				GNC::GCS::Vector m_StartPointMov;

				WFlecha(IWidgetsManager* pManager, long vid, GNC::GCS::Nodo nodos[2], const char* nombre = "");

				~WFlecha();

//endregion

				//region "Serializado y desserializado"
				WFlecha(IWidgetsManager* pManager, long vid, wxXmlNode* nodo);

				wxXmlNode* Serializar(const std::string& nombreMedico);

				//endregion

				virtual bool EsMarcador() const
				{
					return true;
				}

				virtual void GetBoundingBox(GNC::GCS::Vector& bb0, GNC::GCS::Vector& bb1) const
				{
					m_Vertices[0].IniciarBoundingBox(bb0, bb1);
					m_Vertices[1].ExtenderBoundingBox(bb0, bb1);
				}

				virtual bool DelimitaTendencia() const
				{
					return true;
				}

				virtual void GetPuntoAnclaje(GNC::GCS::Vector& punto, const GNC::GCS::Vector& escala) const
				{
					if (m_Vertices[0].m_Seleccionado || m_Vertices[0].m_Iluminado) {
						punto = m_Vertices[0] + GNC::GCS::Vector(10.0f, -10.0f) * escala;
					}
					else {
						punto = m_Vertices[1] + GNC::GCS::Vector(10.0f, -10.0f) * escala;
					}
				}

				//region Propiedades exclusivas de widgets de tendencia

				virtual void GetDistancia(GNC::GCS::Vector& distancia) const
				{
					distancia = m_Vertices[1] - m_Vertices[0];
				}

				virtual void GetRecorrido(std::list<GNC::GCS::Vector>& recorrido) const
				{
					recorrido.push_back(GNC::GCS::Vector(m_Vertices[0]));
					recorrido.push_back(GNC::GCS::Vector(m_Vertices[1]));
				}
				//endregion


				//region "Interfaz especifica"

				virtual bool SoportaAutoBorrado() const {
					return true;
				}

				virtual bool ReservaRecursos() const {
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

				virtual void IluminarNodo( GNC::GCS::Nodo& nodo, bool iluminado);

				virtual void SeleccionarNodo( GNC::GCS::Nodo& nodo, bool seleccionado);

				virtual void Ocultar(bool oculto);

				virtual float Distancia() {
					return m_Distancia;
				}

				//endregion

				//region "Estado interno"
			private:
				bool            m_MouseDown;
				//endregion

				//region "Propiedades geometricas"
			private:
				GNC::GCS::Nodo   m_Centro;
				GNC::GCS::Vector m_CentroAntiguo;
				GNC::GCS::Vector m_Diff;
				float            m_Angulo;
				float            m_Pendiente;
				GNC::GCS::Vector m_TamTexto;

				std::string      m_Texto;

				GNC::GCS::TexturaCairo tc;

				friend std::ostream& operator<<(std::ostream& out, const WFlecha& w) {
					out << "[ P0=" << w.m_Vertices[0] << ", P1=" << w.m_Vertices[1] <<
					", Centro=" << w.m_Centro << ", Angulo=" << w.m_Angulo << "=" << w.m_Angulo*180.0f/M_PI <<
					", Pendiente=" << w.m_Pendiente << ", Longitud=" << w.m_Distancia << ", Cursor=" << w.m_PosCursor << " ]";
					return out;
				}

			public:
				float            m_Distancia;

			public:

				void Recalcular();

			public:
				//endregion
			};
		}
	}
}
